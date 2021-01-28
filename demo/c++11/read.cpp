#include <hx711.hpp>

using namespace avr::io;

int main() {
    hx711::adc<pb6 /*SCK*/, pb7 /*DT*/> adc;
    auto code = adc.read();

}
