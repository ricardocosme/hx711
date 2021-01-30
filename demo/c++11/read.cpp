#include <hx711.hpp>

using namespace avr::io;

int main() {
    auto adc = hx711::make_adc(pb4 /*SCK*/, pb3 /*DOUT*/);
    auto code = adc.read();
}
