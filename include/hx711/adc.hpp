#pragma once

// #include "hx711/avr/gpio.hpp"
#include "hx711/detail/read.hpp"
#include "hx711/gain.hpp"
#include "hx711/lazy_value.hpp"

#include <stdint.h>
#include <util/atomic.h>
#include <util/delay.h>

namespace hx711 {

template<typename SCK, typename DOUT>
class adc {
    uint8_t _state{0};
    const SCK _sck;
    const DOUT _dout;
public:
    using sck_t = SCK;
    using dout_t = DOUT;

    adc(SCK sck, DOUT dout)
        : _sck(sck)
        , _dout(dout)
    {
        using namespace avr::io;
        out(sck);
        low(sck); //normal operation mode
        in(dout);
        high(dout); //enable pullup resistor
    }

    /* Reads an ADC code [synchronous]

       This method blocks until the adc code is available. Take a look
       at async_read() to read without blocking.

       precondition: the adc is powered up.
     */
    int32_t read(gain g = gain::_128) noexcept {
        while(detail::data_is_not_ready(_dout));
        return detail::read(_sck, _dout, g);
    }
    
    /* Reads an ADC code [asynchronous]

       This is an ansychronous operation. The first time that the
       method is called the conversion is started and the method
       returns immediately with a lazy_value(holder for the value
       obtained by the conversion) without any value. Future calls to
       read() may return another lazy_value without anything inside
       with the conversion is not finished, and, it returns a
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

    //power down the adc
    void off() const noexcept {
        high(_sck);
        _delay_us(61);
    }

    //power up the adc
    void on() const noexcept { low(_sck); }
};

template<typename SCK, typename DOUT>
inline adc<SCK, DOUT> make_adc(SCK sck, DOUT dout)
{ return adc<SCK, DOUT>(sck, dout); }

}
