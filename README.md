# Image Processing Project

This project involves implementing a C++ program for representing and processing RGB color images with 8-bits per RGB channel. It includes functionalities such as color representation, image manipulation, script execution, and advanced features like median filtering and XPM2 file loading/saving.

## Features

### Color Representation
- Implemented a class (`Color`) for representing RGB colors.
- Support for accessing individual color channels (red, green, blue).

### Image Representation
- Developed a class (`Image`) for representing images with specified dimensions.
- Included functionalities for pixel manipulation within images.

### Script Processing
- Implemented a script interpreter to execute image processing commands from script files.

### Basic Image Manipulations
- Supported commands for basic image manipulations:
    - Inversion
    - Grayscale conversion
    - Color replacement
    - Filling
    - Horizontal and vertical mirroring

### Dimension-Changing Operations
- Provided commands for manipulating image dimensions:
    - Cropping
    - Rotating left and right

### Advanced Functionality
- Median Filter:
    - Applied a median filter to images for noise reduction.
- XPM2 File Support:
    - Implemented loading and saving images in the XPM2 file format.

## Usage

1. Clone the repository:
```bash
$ git clone git@github.com:YZ1GO/L.EIC009_P_PRJ01.git
```

2. Open project folder in preferred IDE (C++ extensions supported)


3. Build using makefile:
```bash
$ make
```

4. Run the tests:
```bash
$ ./test
```

5. If you wish to recompile everything, clean after testing:
```bash
$ make clean all
```

## Try it yourself

You can find the files for the project and the project assignment [here](files) <br>
[Download Zip File](files/project.zip)
<a href="files/Project assignment.html" target="_blank">Follow the assignment</a>


## Final Grade: 19.80/20

