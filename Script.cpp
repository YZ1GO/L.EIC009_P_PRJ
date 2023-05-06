#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
#include <algorithm> // to use "sort" in "median_filter"
using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            // TODO ...
            if (command == "invert") {
                invert();
                continue;
            }
            if (command == "to_gray_scale") {
                to_gray_scale();
                continue;
            }
            if (command == "replace") {
                replace();
                continue;
            }
            if (command == "fill") {
                fill();
                continue;
            }
            if (command == "h_mirror") {
                h_mirror();
                continue;
            }
            if (command == "v_mirror") {
                v_mirror();
                continue;
            }
            if (command == "add") {
                add();
                continue;
            }
            if (command == "rotate_left") {
                rotate_left();
                continue;
            }
            if (command == "rotate_right") {
                rotate_right();
                continue;
            }
            if (command == "crop") {
                crop();
                continue;
            }
            if (command == "median_filter") {
                median_filter();
                continue;
            }
        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }
    void Script::invert() {
        // loop through all pixels in given image and invert each one by doing (r, g, b) = (255-r, 255-g, 255-b)
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                pixel.red() = 255 - pixel.red();
                pixel.green() = 255 - pixel.green();
                pixel.blue() = 255 - pixel.blue();
            }
        }
    }
    void Script::to_gray_scale() {
        // loop through all pixels in given image and transforms each one to (v, v, v), where v = (r, g, b)/3
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                // calculate v
                rgb_value v = (pixel.red() + pixel.green() + pixel.blue())/3; 
                pixel.red() = v;
                pixel.green() = v;
                pixel.blue() = v;
            }
        }
    }
    void Script::replace() {
        Color target_color, replacement_color; 
        input >> target_color >> replacement_color; // read the color values from the script file ((r1, g1, b1) and (r2, g2, b2))
        
        // loop through all pixels in given image...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                // if pixel's color is equal to target color change it to replacement color 
                if (pixel.red() == target_color.red() && pixel.green() == target_color.green() && pixel.blue() == target_color.blue()) {
                    pixel = replacement_color; // (r1, g1, b1) = (r2, g2, b2)
                }
            }
        }
    }
    void Script::fill() {
        int x, y, w, h;
        Color replacement_color;
        input >> x >> y >> w >> h >> replacement_color; // read the top-left corner (x, y), width value, height value and the color value from the script file
        
        // loop through all pixels in given image...
        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {
                Color& pixel = image->at(i, j);
                // if pixel is located inside the defined rectangle...
                if (i < x + w && i >= x && j < y + h && j >= y) {
                    pixel = replacement_color; // replace it's color to the given one
                }
            }
        }
    }
    void Script::add() {
        string filename;
        Color neutral;
        int x, y;
        input >> filename >> neutral >> x >> y; // read the image "filename", the "neutral" color value and top-left corner (x, y) from the script file
        
        // load "filename" image from the file
        Image* add_image = loadFromPNG(filename);
        
        // loop through all pixels in "filename" image needed to add...
        for (int i = 0; i < add_image->width(); i++) {
            for (int j = 0; j < add_image->height(); j++) {
                Color& add_pixel = add_image->at(i, j);
                // if add_pixel's color isn't the same as the "neutral" color...
                if (add_pixel.red() != neutral.red() || add_pixel.green() != neutral.green() || add_pixel.blue() != neutral.blue()) {
                    image->at(i + x, j + y) = add_pixel; // paste the add_pixel to the current image in the correct position
                }
            }
        }
        delete add_image; // delete the loaded image from the file
    }
    void Script::crop() {
        int x, y, w, h;
        input >> x >> y >> w >> h; // read the top-left corner (x, y), width value and height value from the script file
        
        // create "cropped_image" with "w" width and "h" height
        Image* cropped_image = new Image(w, h);
        
        // loop through all pixels in given image...
        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {
                Color& pixel = image->at(i, j);
                // if pixel is within the cropped range...
                if (i < x + w && i >= x && j < y + h && j >= y) {
                    cropped_image->at(i - x, j - y) = pixel; // paste the pixel to the "crpped_image" in the correct position
                }
            }
        }
        delete image; // delete original image
        image = cropped_image; // move the cropped image to the original image's place since it's empty
    }
    void Script::h_mirror() {
        int w = image->width();
        // mirror image horizontally. Pixels (x, y) and (width() - 1 - x, y) for all 0 <= x < width()/2 and 0 <= y < height()
        for (int x = 0; x < image->width()/2; x++) { // for all pixels through x axis (rightwards) until they reach y axis that splits image into 2 equal halves...
            for (int y = 0; y < image->height(); y++) {
                Color& pixel_1 = image->at(x, y); // get pixel
                Color& pixel_2 = image->at(w - 1 - x, y); // get the symmetric pixel (through y axis)
                Color temp = pixel_1;   // create a temporary color to store "pixel_1"
                pixel_1 = pixel_2;      // change the color of "pixel_1" to it's horizontal symmetric  (pixel_2)
                pixel_2 = temp;         // change the color of "pixel_2" to color of original "pixel_1"
            }
        }
    }
    void Script::v_mirror() {
        int h = image->height();
        // mirror image vertically. Pixels (x, y) and (x, height() - 1 - y) for all 0 <= x < width() and 0 <= y < height()/2
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height()/2; y++) { // for all pixels through y axis (downwards) until they reach x axis that splits image into 2 equal halves...
                Color& pixel_1 = image->at(x, y); // get pixel 
                Color& pixel_2 = image->at(x, h - 1 - y); // get the symmetric pixel (through x axis)
                Color temp = pixel_1;   // create a temporary color to store pixel_1
                pixel_1 = pixel_2;      // change the color of "pixel_1" to it's vertical symmetric  (pixel_2)
                pixel_2 = temp;         // change the color of "pixel_2" to color of original "pixel_1"
            }
        }
    }
    void Script::rotate_left() {
        // create a new image by changing it's width to the original height and it's height to the original width
        Image* rotated_image = new Image(image->height(), image->width());

        // loop through all pixels in given image...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y); // get pixel from original image
                rotated_image->at(y, image->width() - 1 - x) = pixel; // set pixels in rotated image in correct place
            }
        }
        delete image; // delete original image
        image = rotated_image;  // move the rotated image to the original image's place since it's empty
    }
    void Script::rotate_right() {
        // create a new image by changing it's width to the original height and it's height to the original width
        Image* rotated_image = new Image(image->height(), image->width());

        // loop through all pixels in given image...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y); // get pixel from original image
                rotated_image->at(image->height() - 1 - y, x) = pixel; // set pixels in rotated image in correct place
            }
        }
        delete image; //delete original image
        image = rotated_image;  // move the rotated image to the original image's place since it's empty
    }
    void Script::median_filter()
    {
        int ws;
        input >> ws; // read the window size value from the script file

        // create "filtered_image" with the same dimensions as the original image
        Image *filtered_image = new Image(image->width(), image->height());

        // loop through all pixels in given image...
        for (int x = 0; x < image->width(); x++)
        {
            for (int y = 0; y < image->height(); y++)
            {
                vector<rgb_value> red_values;   // create a vector to store the red components
                vector<rgb_value> green_values; // create a vector to store the green components
                vector<rgb_value> blue_values;  // create a vector to store the blue components

                // loop through all neighboring pixels of (x, y)
                for (int nx = max(0, x - ws / 2); nx <= min(image->width() - 1, x + ws / 2); nx++)
                {
                    for (int ny = max(0, y - ws / 2); ny <= min(image->height() - 1, y + ws / 2); ny++)
                    {
                        // if neighboring pixel is within borders...
                        if (nx >= 0 && nx < image->width() && ny >= 0 && ny < image->height())
                        {
                            Color& pixel = image->at(nx, ny);      // get pixel
                            red_values.push_back(pixel.red());     // push back "pixel"'s red component to vector created before
                            green_values.push_back(pixel.green()); // push back "pixel"'s green component to vector created before
                            blue_values.push_back(pixel.blue());   // push back "pixel"'s blue component to vector created before
                        }
                    }
                }

                sort(red_values.begin(), red_values.end());     // sort all red components stored in vector
                sort(green_values.begin(), green_values.end()); // sort all green components stored in vector
                sort(blue_values.begin(), blue_values.end());   // sort all blue components stored in vector

                rgb_value mr; // median value of red components
                rgb_value mg; // median value of green components
                rgb_value mb; // median value of blue components

                // all vector sizes are the same, so create "size" to represent how many components are stored in each vector
                int size = red_values.size();

                // if vector's size is even, median values will be the sum of two middle values divided by 2 or multiplied by 0.5
                if (size % 2 == 0)
                {
                    mr = 0.5 * (red_values[size / 2 - 1] + red_values[size / 2]);
                    mg = 0.5 * (green_values[size / 2 - 1] + green_values[size / 2]);
                    mb = 0.5 * (blue_values[size / 2 - 1] + blue_values[size / 2]);
                }
                // if it's odd, median values are the ones in the middle
                else
                {
                    mr = red_values[size / 2];
                    mg = green_values[size / 2];
                    mb = blue_values[size / 2];
                }

                // change pixels color in "filtered_image" to the median values
                Color& pixel = filtered_image->at(x, y);
                pixel.red() = mr;
                pixel.green() = mg;
                pixel.blue() = mb;
            }
        }
        delete image;           // delete original image
        image = filtered_image; // move the filtered image to the original image's place since it's empty
    }
}
