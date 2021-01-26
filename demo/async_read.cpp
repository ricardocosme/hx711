#include <hx711.hpp>

int main() {
    hx711::adc<PB4 /*SCK*/, PB3 /*DT*/> adc;

    //event loop
    while(true) {
        if(auto code = adc.async_read())
            auto value = code.value();
    }
}
