#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    this->width_ = w;   // width = number of columns
    this->height_ = h;  // height = number of rows
    this->pixels_ = vector<vector<Color>>(height_, vector<Color>(width_, fill)); 
    // create a vector of vectors to represent a 2D matrix and set all pixels to the "fill" color
    // the matrix has "height_" rows and "width_" columns
  }
  Image::~Image() 
  {
  }
  int Image::width() const
  {
    return width_;  // get width value
  }
  int Image::height() const
  {
    return height_; // get height value
  }

  // TODO: remove this DUMMY_color variable once you have appropriate fields for representing image pixels.
  // Color DUMMY_color;

  Color& Image::at(int x, int y)
  {
    return pixels_[y][x]; // get color of pixel which value can be changed
  }

  const Color& Image::at(int x, int y) const
  {
    return pixels_[y][x]; // get color of pixel which value cannot be changed
  }
}
