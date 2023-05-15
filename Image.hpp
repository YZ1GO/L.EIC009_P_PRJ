#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector> // to create a vector to store pixels data
using namespace std;

namespace prog
{
  class Image
  {
  private:
    int width_;   // variable for width
    int height_;  // variable for height
    vector<vector<Color>> pixels_;  // variable for matrix that stores all pixels from an image
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
  };
}
#endif
