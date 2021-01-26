#include <hx711.hpp>
#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85::ssd1306;

int main() {
    display_128x64<> disp;
    disp.on();
    disp.clear();

    hx711::hx711<PB4 /*SCK*/, PB3 /*DT*/> scale;

    uint32_t timer{0};
    while(true) {
        ++timer;
        auto adc_code = hx711::sync_read(scale);
        disp.out<font::_8x8>(0, 0, adc_code);
        disp.out<font::_8x8>(2, 0, timer);
        timer = 0;
        // if(auto adc_code = scale.read()) {
        //     disp.out<font::_8x8>(0, 0, adc_code.value());
        //     disp.out<font::_8x8>(2, 0, timer);
        //     timer = 0;
        // }
    }
}
