#pragma once

#include "hx711/avr/gpio.hpp"
#include "hx711/lazy_value.hpp"
#include <stdint.h>
#include <util/atomic.h>

namespace hx711 {

template<uint8_t SCK, uint8_t DOUT>
class hx711 {
    uint8_t _state{0};
public:
    constexpr static uint8_t sck = SCK;
    constexpr static uint8_t dout = DOUT;
    
    hx711() {
        out(sck);
        low(sck); //normal operation mode
        in(dout);
        high(dout); //enable pullup resistor
    }

    /* Reads an ADC code

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
     */
    lazy_value read() noexcept {
        switch(_state) {
        case 0: {
            while(PINB & (1<<DOUT)) {
                _state = 1;
                return {};
            case 1: {}
            }
        }
        default: {
            int32_t code{};
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                for(uint8_t i{24}; i > 0; --i){
                    high(sck);
                    low(sck);
                    code <<= 1;
                    if(PINB & (1<<DOUT)) ++code;
                }
                high(sck);
                low(sck);
            }
            _state = 0;
            if(code & 0x00800000) code |= 0xFF000000;
            return code;
        }
        }
        return {};
    }
};

}
