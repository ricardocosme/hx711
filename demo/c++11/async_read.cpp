#include <hx711.hpp>

using namespace avr::io;

int main() {
    hx711::adc<pb4 /*SCK*/, pb3 /*DT*/> adc;

    //event loop
    while(true) {
        if(auto code = adc.async_read())
            auto value = code.value();
    }
}
