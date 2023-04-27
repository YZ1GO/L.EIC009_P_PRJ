#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void invert(); // function to invert the color of each individual pixel
    void to_gray_scale(); // function to transform each individual pixel (r, g, b) to (v, v, v) where v = (r, g, b)/3
    void replace(rgb_value r1, rgb_value g1, rgb_value b1, rgb_value r2, rgb_value g2, rgb_value b2); // function to replace all (r1, g1, b1) pixels by (r2, g2, b2)
    void h_mirror(); // function to mirror image horizontally
    void v_mirror(); // function to mirror image vertically
    void rotate_left();
    void rotate_right();
  };
}
#endif
