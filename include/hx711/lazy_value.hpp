#pragma once

#include <limits>
#include <stdint.h>

namespace hx711 {

class lazy_value {
    int32_t _value{std::numeric_limits<int32_t>::max()};
public:
    using value_type = int32_t;
    lazy_value() = default;
    lazy_value(int32_t v) : _value(v) {}
    bool done() const noexcept
    { return _value != std::numeric_limits<int32_t>::max(); }
    operator bool() const noexcept { return done(); }
    int32_t value() const noexcept { return _value; }
};

}
