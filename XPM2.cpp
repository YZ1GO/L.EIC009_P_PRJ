#include "XPM2.hpp"
#include <fstream> // to manipulate files
#include <unordered_map> // to use "unordered_map"
#include <map> // to use "map"

namespace prog {

    Image* loadFromXPM2(const std::string& file) {
        ifstream in(file); // open file to read

        string header; 
        in >> header >> header; // get first line of the file "! XPM2"
        
        int width, height, num_colors, char_per_color;
        in >> width >> height >> num_colors >> char_per_color; // get values from the 2nd line of the file
        
        unordered_map<string, Color> all_colors; // create a data structure to store mapped colors in key-value style

        for (int i = 0; i < num_colors; i++) {
            string c, no_use, hexcode; 
            in >> c >> no_use >> hexcode; // get character and respective hexcode color
            all_colors.insert(make_pair(c, Color(hexcode))); // insert key(character) and value(hexcode), note value stored as rgb values
        }

        Image* image = new Image(width, height); // create new image

        // loop through all lines that contain pixel encoding...
        for (int y = 0; y < height; y++) { 
            string line;
            in >> line;
            for (int x = 0; x < width; x++) {
                image->at(x, y) = all_colors[line.substr(x, 1)]; // change every single pixel in image to corresponding encoded color
            }
        }

        return image;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        ofstream out(file); // open file to write

        map<Color, string> all_colors; // create a data structure to store colors and their respective encoding character

        char encode = '*'; // variable to encode first color

        // loop through all pixels in given image...
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                Color pixel = image->at(x, y);

                // if "pixel" is not stored...
                if(all_colors.find(pixel) == all_colors.end()) {
                    all_colors[pixel] = encode; // insert "pixel" and a respective encoding character
                    encode++; // change encoding character to other one
                }
            }
        }

        out << "! XPM2" << endl; // write header in file
        out << image->width() << " " << image->height() << " " << all_colors.size() << " 1" << endl; // write the values in second line of the file

        // iterate through all pairs stored...
        for (const auto& color : all_colors) {
            string hexcode = Color::rgb_to_hexcode(color.first); // change color to hexcode string
            out << color.second << " c " << hexcode << endl; // write lines that show which character is mapped to which color
        }

        // write all lines that contain pixel encoding
        for (int y = 0; y < image->height(); y++) {
            string line;
            for (int x = 0; x < image->width(); x++) {
                Color pixel = image->at(x, y);
                line += all_colors[pixel];
            }
            out << line << endl;
        }
    }
}
