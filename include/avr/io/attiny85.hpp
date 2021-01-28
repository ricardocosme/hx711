#pragma once

#include <avr/io/portxn.hpp>

namespace avr { namespace io {

/*Port B*/
template<uint8_t n>
struct portBn : portxn<0x16, 0x17, 0x18, n> {};

struct pb0_t : portBn<0> {};
struct pb1_t : portBn<1> {};
struct pb2_t : portBn<2> {};
struct pb3_t : portBn<3> {};
struct pb4_t : portBn<4> {};
struct pb5_t : portBn<5> {};

#if (__cplusplus >= 201703L)
inline constexpr pb0_t pb0;
inline constexpr pb1_t pb1;
inline constexpr pb2_t pb2;
inline constexpr pb3_t pb3;
inline constexpr pb4_t pb4;
inline constexpr pb5_t pb5;
#else
using pb0 = pb0_t;
using pb1 = pb1_t;
using pb2 = pb2_t;
using pb3 = pb3_t;
using pb4 = pb4_t;
using pb5 = pb5_t;
#endif

}}
