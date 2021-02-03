#pragma once

#include "hx711/gain.hpp"

#include <avr/io/io.hpp>
#include <stdint.h>
#include <util/atomic.h>

namespace hx711 { namespace detail {

template<typename DOUT>
[[gnu::always_inline]]
inline bool data_is_not_ready(DOUT dout) noexcept
{ return avr::io::is_high(dout); }

template<typename SCK, typename DOUT>
inline int32_t read(SCK sck, DOUT dout, gain g) noexcept {
    using namespace avr::io;
    int32_t code{};
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for(uint8_t i{24}; i > 0; --i){
            high(sck);
            low(sck);;
            code <<= 1;
            if(is_high(dout)) ++code;
        }
        high(sck);
        low(sck);;
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

}}
