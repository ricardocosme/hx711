#include <hx711.hpp>

int main() {
    hx711::adc<PB4 /*SCK*/, PB3 /*DT*/> adc;

    auto code = adc.read(); // gain=128
    auto code_64 = adc.read(hx711::gain::_64); // gain=64
    auto code_32 = adc.read(hx711::gain::_32); // gain=32
}
