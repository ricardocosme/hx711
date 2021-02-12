#include <hx711.hpp>

using namespace avr::io;

int main() {
    auto adc = hx711::make_adc(pb4 /*PD_SCK*/, pb3 /*DOUT*/);
    
    //event loop
    while(true) {
        if(auto code = adc.async_read())
            auto value = code.value();
    }
}
