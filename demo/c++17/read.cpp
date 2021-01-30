#include <hx711.hpp>

using namespace avr::io;

int main() {
    hx711::adc adc{pb4, pb3};
    auto code = adc.read();
}
