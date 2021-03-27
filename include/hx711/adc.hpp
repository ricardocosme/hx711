#pragma once

#include "hx711/detail/read.hpp"
#include "hx711/gain.hpp"
#include "hx711/lazy_value.hpp"

#include <avr/io.hpp>
#include <stdint.h>
#include <util/delay.h>

namespace hx711 {

/** Represents one HX711

    The pins from the MCU that are connecting the pins of the ADC
    named PD_SCK(Power down control and serial clock input) and
    DOUT(Serial data output) should be passed to the constructor. The
    constructor assumes the responsibility of initialize these pins to
    the state that is required.
 */
template<typename PD_SCK, typename DOUT>
#if __cplusplus > 201703L //Use concepts if c++20 is available
requires avr::io::Pin<PD_SCK> && avr::io::Pin<DOUT>
#endif
class adc {
    uint8_t _state{0};
    PD_SCK _sck;
    DOUT _dout;
public:
    using sck_t = PD_SCK;
    using dout_t = DOUT;

    adc() = default;
    
    adc(PD_SCK sck, DOUT dout) noexcept
        : _sck(sck)
        , _dout(dout)
    {
        using namespace avr::io;
        out(sck);
        low(sck); //normal operation mode
        in(pullup, dout);
    }

    /** Reads an ADC code [synchronous]

        This method blocks until the adc code is available. Take a look
        at async_read() to read without blocking.

        precondition: the adc is powered up.
     */
    int32_t read(gain g = gain::_128) noexcept {
        while(detail::data_is_not_ready(_dout));
        return detail::read(_sck, _dout, g);
    }
    
    /** Reads an ADC code [asynchronous]

        This is an ansychronous operation. The first time that the
        method is called the conversion is started and the method
        returns immediately with a lazy_value(holder for the value
        obtained by the conversion) without any value inside. Future
        calls to read() may return another lazy_value without anything
        inside when the conversion is not finished, and, it returns a
        lazy_value with the outcome if the conversion is done.

        Usage: 
          One common and expected usage of this method is inside
          an event loop. For example, the read() can be called inside an
          ISR related to a timer:

          //ISR timer
          {
            if(auto code = adc.read())
              do_something(code);
          }

          Take a look at sync_read.hpp if a synchronous reading is
          desired.

        precondition: the adc is powered up.
     */
    lazy_value async_read(gain g = gain::_128) noexcept {
        switch(_state) {
        case 0: {
            while(detail::data_is_not_ready(_dout)) {
                _state = 1;
                return {};
            case 1: {}
            }
        }
        default: {
            _state = 0;
            return detail::read(_sck, _dout, g);
        }
        }
        return {};
    }

    /** Power down the adc. */
    void off() const noexcept {
        high(_sck);
        _delay_us(61);
    }

    /** Power up the adc. */
    void on() const noexcept { low(_sck); }
};

//Note, this is only intended to be used with C++11/14.
template<typename PD_SCK, typename DOUT>
inline adc<PD_SCK, DOUT> make_adc(PD_SCK sck, DOUT dout)
{ return adc<PD_SCK, DOUT>(sck, dout); }

}
