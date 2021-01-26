#include <hx711.hpp>

void do_something(int32_t code) {}

int main() {
    hx711::hx711<PB4 /*SCK*/, PB3 /*DT*/> adc;

    while(true) {
        if(auto code = adc.read())
            do_something(code.value());
    }
}
