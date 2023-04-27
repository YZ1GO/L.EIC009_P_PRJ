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
    void replace(); // function to replace all (r1, g1, b1) pixels by (r2, g2, b2)
    void fill(); // function to assign (r, g, b) to all pixels contained in rectangle defined by top-left corner (x, y), width w, height h
    void add(); // function to copy all pixels from image stored in "filename", except pixels with "neutral" color, to the rectangle defined by top-left corner (x, y)
    void h_mirror(); // function to mirror image horizontally
    void v_mirror(); // function to mirror image vertically
    void crop(); // function to crop image, reducing it to all pixels contained in the rectangle defined by top-left corner (x, y), width w and height h
    void rotate_left(); // function to rotate image to the left
    void rotate_right(); // function to rotate image to the right
  };
}
#endif
