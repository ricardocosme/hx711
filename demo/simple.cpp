#include <hx711.hpp>
#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>
#include <stdlib.h>
#include <math.h>
using namespace att85::ssd1306;

int main() {
    display_128x64<> disp;
    disp.on();
    disp.clear();

    hx711::sensor<PB4, PB3> scale;

    int32_t tare{0};
    for(auto i{0}; i < 20; ++i)
        tare += hx711::sync_read(scale);
    tare /= 20;
    
    disp.out<font::_8x8>(0, 0, (uint32_t)tare);
    
    int32_t curr{0};
    static_assert(std::numeric_limits<uint32_t>::max() == 4294967295);
    while(true) {
        int32_t sample{0};
        for(auto i{0}; i < 1; ++i)
            sample += hx711::sync_read(scale);
        sample /= 1;
        
        disp.out<font::_8x8>(2, 0, (uint32_t)sample);
        sample -= tare;
        disp.out<font::_8x8>(4, 0, ATT85_SSD1306_STR("        "));
        
        if((sample - curr) < 0) {
            disp.out<font::_8x8>(4, 0, ATT85_SSD1306_STR("n"));
            disp.out<font::_8x8>(4, 10, (uint32_t)abs(sample - curr));
        } else {
            disp.out<font::_8x8>(4, 0, ATT85_SSD1306_STR(" "));
            disp.out<font::_8x8>(4, 10, (uint32_t)abs(sample - curr));
        }
        
        if(sample < 0 || (sample <= 108)) {
            curr = sample;
            disp.out<font::_8x8>(6, 70, ATT85_SSD1306_STR("        "));
            disp.out<font::_8x8>(6, 70, (uint32_t)0);
            continue;
        }
        
        if(abs(sample - curr) <= 108) continue;
        disp.out<font::_8x8>(6, 0, (uint32_t)sample);
        curr = sample;
        
        auto w = (static_cast<uint32_t>(sample) * 100 / 1075);
        disp.out<font::_8x8>(6, 70, ATT85_SSD1306_STR("        "));
        disp.outf<font::_8x8>(6, 70, w);
    }
}
