#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

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
            //if (command == "replace") {
            //    replace(rgb_value r1, rgb_value g1, rgb_value b1, rgb_value r2, rgb_value g2, rgb_value b2);
            //    continue;
            //}
            if (command == "h_mirror") {
                h_mirror();
                continue;
            }
            if (command == "v_mirror") {
                v_mirror();
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
        // loop through all pixels in given image and transforms each one to (v, v, v) where v = (r, g, b)/3
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                rgb_value v = (pixel.red() + pixel.green() + pixel.blue())/3;
                pixel.red() = v;
                pixel.green() = v;
                pixel.blue() = v;
            }
        }
    }
    void Script::replace(rgb_value r1, rgb_value g1, rgb_value b1, rgb_value r2, rgb_value g2, rgb_value b2) {
        // loop through all pixels in given image and replaces all (r1, g1, b1) pixels by (r2, g2, b2)
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y);
                if (pixel.red() == r1 && pixel.green() == g1 && pixel.blue() == b1) {
                    pixel.red() = r2;
                    pixel.green() = g2;
                    pixel.blue() = b2;
                }
            }
        }
    }
    
    void Script::h_mirror() {
        int w = image->width();
        // mirror image horizontally. Pixels (x, y) and (width() - 1 - x, y) for all 0 <= x < width()/2 and 0 <= y < height()
        for (int x = 0; x < image->width()/2; x++) { // for all pixels through x axis (rightwards) until it reaches y axis that splits image into 2 equal halves
            for (int y = 0; y < image->height(); y++) {
                Color& pixel_1 = image->at(x, y); // get pixel
                Color& pixel_2 = image->at(w - 1 - x, y); // get the symmetric pixel (through y axis)
                Color temp = pixel_1;   // create a temporary color to store pixel_1
                pixel_1 = pixel_2;      // change the color of pixel_1 to it's horizontal symmetric  (pixel_2)
                pixel_2 = temp;         // change the color of pixel_2 to color of original pixel_1
            }
        }
    }
    void Script::v_mirror() {
        int h = image->height();
        // mirror image vertically. Pixels (x, y) and (x, height() - 1 - y) for all 0 <= x < width() and 0 <= y < height()/2
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height()/2; y++) { // for all pixels through y axis (downwards) until it reaches x axis that splits image into 2 equal halves
                Color& pixel_1 = image->at(x, y); // get pixel 
                Color& pixel_2 = image->at(x, h - 1 -y); // get the symmetric pixel (through x axis)
                Color temp = pixel_1;   // create a temporary color to store pixel_1
                pixel_1 = pixel_2;      // change the color of pixel_1 to it's vertical symmetric  (pixel_2)
                pixel_2 = temp;         // change the color of pixel_2 to color of original pixel_1
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
                rotated_image->at(y, image->width() - 1 - x) = pixel; // set pixels in rotated image
            }
        }
        delete image; // eliminate original image
        image = rotated_image;  // move the rotated image to the original image's place since it's empty
    }
    void Script::rotate_right() {
        // create a new image by changing it's width to the original height and it's height to the original width
        Image* rotated_image = new Image(image->height(), image->width());

        // loop through all pixels in given image...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color& pixel = image->at(x, y); // get pixel from original image
                rotated_image->at(image->height() - 1 - y, x) = pixel; // set pixels in rotated image
            }
        }
        delete image; //eliminate original image
        image = rotated_image;  // move the rotated image to the original image's place since it's empty
    }

}
