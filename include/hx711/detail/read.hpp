#pragma once

#include "hx711/gain.hpp"

#include <avr/interrupt.hpp>
#include <avr/io.hpp>
#include <stdint.h>

namespace hx711 { namespace detail {

template<typename DOUT>
[[gnu::always_inline]]
inline bool data_is_not_ready(DOUT dout) noexcept
{ return avr::io::is_high(dout); }

template<typename Pin>
[[gnu::always_inline]]
inline void pulse(Pin pin) noexcept {
    high(pin);
    low(pin);
}

template<typename PD_SCK, typename DOUT>
#if __cplusplus > 201703L //Use concepts if c++20 is available
requires avr::io::Pin<PD_SCK> && avr::io::Pin<DOUT>
#endif
inline int32_t read(PD_SCK sck, DOUT dout, gain g) noexcept {
    using namespace avr::io;
    using namespace avr::interrupt;
    int32_t code{};
    {
        atomic<> s;
        for(uint8_t i{24}; i > 0; --i){
            pulse(sck);
            code <<= 1;
            if(is_high(dout)) ++code;
        }
        for(uint8_t i{0}; i <= static_cast<uint8_t>(g); ++i) 
            pulse(sck);
    }
    if(code & 0x00800000) code |= 0xFF000000;
    return code;
}

}}
