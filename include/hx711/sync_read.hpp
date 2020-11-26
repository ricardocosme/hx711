#pragma once

#include "hx711/sensor.hpp"

#include <stdint.h>

namespace hx711 {

template<typename Sensor>
inline auto sync_read(Sensor& sensor) noexcept {
    while(true) {
        if(auto t = sensor.read())
            return t.value();
    }
}

}
