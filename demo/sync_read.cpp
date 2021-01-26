#include <hx711.hpp>

void do_something(int32_t code) {}

int main() {
    hx711::hx711<PB4 /*SCK*/, PB3 /*DT*/> adc;

    while(true) {
        do_something(hx711::sync_read(adc));
    }
}
