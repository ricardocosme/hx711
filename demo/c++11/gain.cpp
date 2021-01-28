#include <hx711.hpp>

using namespace avr::io;

int main() {
    hx711::adc<pb4 /*SCK*/, pb3 /*DT*/> adc;

    auto code = adc.read(); // gain=128
    auto code_64 = adc.read(hx711::gain::_64); // gain=64
    auto code_32 = adc.read(hx711::gain::_32); // gain=32
}
