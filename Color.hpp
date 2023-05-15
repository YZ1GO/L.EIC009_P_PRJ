#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

#include <string> // for the extra function hexcode to rgb implemented
using namespace std;

namespace prog
{
  typedef unsigned char rgb_value;
  class Color
  {
    private:
      // TODO: private fields required for color representation.
      rgb_value r;  // variable for red component
      rgb_value g;  // variable for green component
      rgb_value b;  // variable for blue component
    public:
      Color();
      Color(const Color& c);
      Color(rgb_value r, rgb_value g, rgb_value b);
      rgb_value red() const;
      rgb_value& red();
      rgb_value green() const;
      rgb_value& green();
      rgb_value blue() const;
      rgb_value& blue();
      Color(const string& hexcode); // function to turn hexcode color to rgb color
      static string rgb_to_hexcode(const Color& c); // function to turn rgb color to a string representing hexcode color
      bool operator<(const Color& other) const; // "operator<" to allow to implement map<Color, string>
  };
}
#endif
