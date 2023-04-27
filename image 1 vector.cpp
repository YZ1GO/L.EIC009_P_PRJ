#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    this->width_ = w;
    this->height_ = h;
    for (int i = 0; i < w * h; i++) // for all pixels in image created with size = width_ * height_...
    {
      pixels_.push_back(fill);
      // pixels are stored in vector "pixels_" row by row, pixel by pixel
      // e.g. an image 3x3, pixels_[3] will store the pixel(0, 1) which is located in row #2 column #1 (see below)
      //  # # #
      //  p # #
      //  # # #
    }
    this->pixels_ = pixels_;
  }
  Image::~Image()
  {
  }
  int Image::width() const
  {
    return width_; // get width
  }
  int Image::height() const
  {
    return height_; // get height
  }

  // TODO: remove this DUMMY_color variable once you have appropriate fields for representing image pixels.
  // Color DUMMY_color;

  Color &Image::at(int x, int y)
  {
    return pixels_[width_ * y + x]; // width_*y to get to the row then add x to get index of the pixel wanted
  }

  const Color &Image::at(int x, int y) const
  {
    return pixels_[width_ * y + x]; // width_*y to get to the row then add x to get index of the pixel wanted
  }
}
