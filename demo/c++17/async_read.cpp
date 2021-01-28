#include <hx711.hpp>

using namespace avr::io;

int main() {
    hx711::adc adc{pb4, pb3};

    //event loop
    while(true) {
        if(auto code = adc.async_read())
            auto value = code.value();
    }
}
