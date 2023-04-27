#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    this->width_ = w;   // width = number of columns
    this->height_ = h;  // height = number of rows
    this->pixels_ = vector<vector<Color>>(height_, vector<Color>(width_, fill)); 
    // create a vector of vectors to represent a 2D matrix and set all pixels to the "fill" color
  }
  Image::~Image() 
  {
  }
  int Image::width() const
  {
    return width_;  // get width
  }
  int Image::height() const
  {
    return height_; // get height
  }

  // TODO: remove this DUMMY_color variable once you have appropriate fields for representing image pixels.
  // Color DUMMY_color;

  Color& Image::at(int x, int y)
  {
    return pixels_[y][x]; // get color of pixel being able to change it's value
  }

  const Color& Image::at(int x, int y) const
  {
    return pixels_[y][x]; // get color of pixel without being able to change it's value
  }
}
