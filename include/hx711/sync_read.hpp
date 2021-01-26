#pragma once

#include "hx711/hx711.hpp"

namespace hx711 {

//Synchronous reading
template<typename HX711>
inline auto sync_read(HX711& adc) noexcept {
    while(true) {
        if(auto t = adc.read())
            return t.value();
    }
}

}
