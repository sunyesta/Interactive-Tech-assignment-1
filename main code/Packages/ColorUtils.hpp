

#pragma once
#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

// SRC: https://www.programmingalgorithms.com/algorithm/hsl-to-rgb/cpp/

class RGB {
   public:
    unsigned char R;
    unsigned char G;
    unsigned char B;

    RGB(unsigned char r, unsigned char g, unsigned char b);

    bool Equals(RGB rgb);
};

class HSL {
   public:
    int H;
    float S;
    float L;

    HSL(int h, float s, float l);
    bool Equals(HSL hsl);
};

static float HueToRGB(float v1, float v2, float vH);

static RGB HSLToRGB(HSL hsl);

#endif /* COLOR_UTILS_HPP */