#include <hx711.hpp>

int main() {
    hx711::adc<PB4 /*SCK*/, PB3 /*DT*/> adc;
    auto code = adc.read();
}
