#pragma once

#include <avr/io/portxn.hpp>

namespace avr { namespace io {

/*Port B*/
template<uint8_t n>
struct portBn : portxn<0x03, 0x04, 0x05, n> {};

struct pb0_t : portBn<0> {};
struct pb1_t : portBn<1> {};
struct pb2_t : portBn<2> {};
struct pb3_t : portBn<3> {};
struct pb4_t : portBn<4> {};
struct pb5_t : portBn<5> {};
struct pb6_t : portBn<6> {};
struct pb7_t : portBn<7> {};

#if (__cplusplus >= 201703L)
inline constexpr pb0_t pb0;
inline constexpr pb1_t pb1;
inline constexpr pb2_t pb2;
inline constexpr pb3_t pb3;
inline constexpr pb4_t pb4;
inline constexpr pb5_t pb5;
inline constexpr pb6_t pb6;
inline constexpr pb7_t pb7;
#else
using pb0 = pb0_t;
using pb1 = pb1_t;
using pb2 = pb2_t;
using pb3 = pb3_t;
using pb4 = pb4_t;
using pb5 = pb5_t;
using pb6 = pb6_t;
using pb7 = pb7_t;
#endif

/*Port C*/
template<uint8_t n>
struct portCn : portxn<0x06, 0x07, 0x08, n> {};

struct pc0_t : portCn<0> {};
struct pc1_t : portCn<1> {};
struct pc2_t : portCn<2> {};
struct pc3_t : portCn<3> {};
struct pc4_t : portCn<4> {};
struct pc5_t : portCn<5> {};
struct pc6_t : portCn<6> {};

#if (__cplusplus >= 201703L)
inline constexpr pc0_t pc0;
inline constexpr pc1_t pc1;
inline constexpr pc2_t pc2;
inline constexpr pc3_t pc3;
inline constexpr pc4_t pc4;
inline constexpr pc5_t pc5;
inline constexpr pc6_t pc6;
#else
using pc0 = pc0_t;
using pc1 = pc1_t;
using pc2 = pc2_t;
using pc3 = pc3_t;
using pc4 = pc4_t;
using pc5 = pc5_t;
using pc6 = pc6_t;
#endif

/*Port D*/
template<uint8_t n>
struct portDn : portxn<0x09, 0x0A, 0x0B, n> {};

struct pd0_t : portCn<0> {};
struct pd1_t : portCn<1> {};
struct pd2_t : portCn<2> {};
struct pd3_t : portCn<3> {};
struct pd4_t : portCn<4> {};
struct pd5_t : portCn<5> {};
struct pd6_t : portCn<6> {};

#if (__cplusplus >= 201703L)
inline constexpr pd0_t pd0;
inline constexpr pd1_t pd1;
inline constexpr pd2_t pd2;
inline constexpr pd3_t pd3;
inline constexpr pd4_t pd4;
inline constexpr pd5_t pd5;
inline constexpr pd6_t pd6;
#else
using pd0 = pd0_t;
using pd1 = pd1_t;
using pd2 = pd2_t;
using pd3 = pd3_t;
using pd4 = pd4_t;
using pd5 = pd5_t;
using pd6 = pd6_t;
#endif

}}
