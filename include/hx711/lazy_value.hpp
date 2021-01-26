#pragma once

#include <stdint.h>

namespace hx711 {

/* Represents a future value

   If there isn't any value yet the method done() returns false and
   true otherwise. If done() == true then the value can be obtained
   through value().
 */
class lazy_value {
    int32_t _value{INT32_MAX};
public:
    using value_type = int32_t;
    
    lazy_value() = default;
    
    lazy_value(int32_t v) : _value(v) {}
    
    bool done() const noexcept
    { return _value != INT32_MAX; }
    
    operator bool() const noexcept { return done(); }

    //precondition: done() == true
    int32_t value() const noexcept { return _value; }
};

}
