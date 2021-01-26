#pragma once

#include "hx711/avr/gpio.hpp"
#include "hx711/gain.hpp"

#include <stdint.h>
#include <util/atomic.h>

namespace hx711::detail {

[[gnu::always_inline]]
inline bool data_is_not_ready(uint8_t dout) noexcept
{ return PINB & (1<<dout); }

inline auto read(uint8_t sck, uint8_t dout, gain g) noexcept {
    int32_t code{};
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for(uint8_t i{24}; i > 0; --i){
            high(sck);
            low(sck);
            code <<= 1;
            if(PINB & (1<<dout)) ++code;
        }
        high(sck);
        low(sck);
        if(g == gain::_32) {
            high(sck);
            low(sck);
        } else if(g == gain::_64) {
            high(sck);
            low(sck);
            high(sck);
            low(sck);
        }
    }
    if(code & 0x00800000) code |= 0xFF000000;
    return code;
}

}
