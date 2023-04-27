#include "Color.hpp"

namespace prog {
    Color::Color() {
        // default constructor with color = black
        r = 0;
        g = 0;
        b = 0;
    }
    Color::Color(const Color& other) {
        // copy constructor
        r = other.r; 
        g = other.g;
        b = other.b;
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        // constructor supplied (r, g, b) values
        this->r = red;
        this->g = green;
        this->b = blue;
    }
    rgb_value Color::red() const {
        return r;   //get red component
    }
    rgb_value Color::green() const {
        return g;   //get green component
    }
    rgb_value Color::blue() const {
        return b;   //get blue component
    }

    // TODO: remove this DUMMY variable once you have appropriate fields for representing colors.
    // rgb_value DUMMY_rgb_value = 0; 

    rgb_value& Color::red()  {
        // mutator for red component
        rgb_value& red_mutator = r;
        return red_mutator;
    }
    rgb_value& Color::green()  {
        // mutator for green component
        rgb_value& green_mutator = g;
        return green_mutator;
    }
    rgb_value& Color::blue()  {
        // mutator for blue component
        rgb_value& blue_mutator = b;
        return blue_mutator;
    }
}
