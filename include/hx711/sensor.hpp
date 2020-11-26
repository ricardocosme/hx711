#pragma once

#include "hx711/avr/gpio.hpp"
#include "hx711/lazy_value.hpp"
#include <util/atomic.h>

namespace hx711 {

template<uint8_t SCK, uint8_t DT>
class sensor {
    uint8_t _state{0};
public:
    constexpr static uint8_t sck = SCK;
    constexpr static uint8_t dt = DT;
    sensor() {
        out(sck);
        low(sck); // Do I need this?
        in(dt);
        high(dt); //enable pullup resistor
    }

    lazy_value read() noexcept {
        switch(_state) {
        case 0: {
            while(PINB & (1<<DT)) {
                _state = 1;
                return {};
            case 1: {}
            }
        }
        default: {
            int32_t v{};
            ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
                for(uint8_t i{24}; i > 0; --i){
                    high(sck);
                    low(sck);
                    v <<= 1;
                    if(PINB & (1<<DT)) ++v;
                }
                high(sck);
                low(sck);
            }
            _state = 0;
            if(v & 0x00800000) v |= 0xFF000000;
            return v;
        }
        }
        return {};
    }
};

}
