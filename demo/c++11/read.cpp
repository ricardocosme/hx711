#include <hx711.hpp>

using namespace avr::io;

int main() {
    hx711::adc<pb4 /*SCK*/, pb3 /*DT*/> adc;
    auto code = adc.read();

}
