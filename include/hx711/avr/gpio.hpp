#pragma once


template<typename Pin>
[[gnu::always_inline]]
inline void low()
{ *Pin::portB = *Pin::portB & ~(1 << Pin::num); }

template<typename Pin>
[[gnu::always_inline]]
inline void high()
{ *Pin::portB = *Pin::portB | (1 << Pin::num); }

template<typename Pin>
[[gnu::always_inline]]
inline void out()
{ *Pin::ddrB = *Pin::ddrB | (1 << Pin::num); }

template<typename Pin>
[[gnu::always_inline]]
inline void in()
{ *Pin::ddrB = *Pin::ddrB & ~(1 << Pin::pin); }
