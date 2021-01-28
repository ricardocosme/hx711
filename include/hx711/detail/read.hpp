#pragma once

#include "hx711/gain.hpp"

#include <avr/io/io.hpp>
#include <stdint.h>
#include <util/atomic.h>

namespace hx711 { namespace detail {

template<typename DOUT>
[[gnu::always_inline]]
inline bool data_is_not_ready() noexcept
{ return DOUT::read(); }

template<typename SCK, typename DOUT>
inline int32_t read(gain g) noexcept {
    int32_t code{};
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for(uint8_t i{24}; i > 0; --i){
            SCK::high();
            SCK::low();;
            code <<= 1;
            if(DOUT::read()) ++code;
        }
        SCK::high();
        SCK::low();;
        if(g == gain::_32) {
            SCK::high();
            SCK::low();;
        } else if(g == gain::_64) {
            SCK::high();
            SCK::low();;
            SCK::high();
            SCK::low();;
        }
    }
    if(code & 0x00800000) code |= 0xFF000000;
    return code;
}

}}
