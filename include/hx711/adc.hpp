#pragma once

#include "hx711/avr/gpio.hpp"
#include "hx711/detail/read.hpp"
#include "hx711/gain.hpp"
#include "hx711/lazy_value.hpp"

#include <stdint.h>
#include <util/atomic.h>
#include <util/delay.h>

namespace hx711 {

template<uint8_t SCK, uint8_t DOUT>
class adc {
    uint8_t _state{0};
public:
    constexpr static uint8_t sck = SCK;
    constexpr static uint8_t dout = DOUT;
    
    adc() {
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
    auto read(gain g = gain::_128) noexcept {
        while(detail::data_is_not_ready(dout));
        return detail::read(sck, dout, g);
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
            while(detail::data_is_not_ready(dout)) {
                _state = 1;
                return {};
            case 1: {}
            }
        }
        default: {
            _state = 0;
            return detail::read(sck, dout, g);
        }
        }
        return {};
    }

    //power down the adc
    void off() const noexcept {
        high(sck);
        _delay_us(61);
    }

    //power up the adc
    void on() const noexcept { low(sck); }
};

}
