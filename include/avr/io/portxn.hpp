#pragma once

#include <stdint.h>

namespace avr { namespace io {

[[gnu::always_inline]]
inline volatile uint8_t* to_addr(uint8_t i)
{return reinterpret_cast<volatile uint8_t*>(i + 0x20); }

template<
    uint8_t pin_addr,
    uint8_t ddr_addr,
    uint8_t port_addr,
    uint8_t pin_num>
struct portxn {
    static const uint8_t num{pin_num};
    
    static volatile uint8_t* pin() noexcept
    { return to_addr(pin_addr); }
    
    static volatile uint8_t* ddr() noexcept
    { return to_addr(ddr_addr); }
    
    static volatile uint8_t* port() noexcept
    { return to_addr(port_addr); }

    [[gnu::always_inline]]
    static void low() noexcept
    { *port() = *port() & ~(1 << num); }
    
    [[gnu::always_inline]]
    static void high() noexcept
    { *port() = *port() | (1 << num); }

    [[gnu::always_inline]]
    static void out() noexcept
    { *ddr() = *ddr() | (1 << num); }

    [[gnu::always_inline]]
    static void in() noexcept
    { *ddr() = *ddr() & ~(1 << num); }

    [[gnu::always_inline]]
    static bool read() noexcept
    { return *pin() & (1<<num); }
};


}}
