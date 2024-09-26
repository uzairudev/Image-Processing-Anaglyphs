# Image Processing Anaglyphs

This repository contains a C++ program that generates different types of anaglyph images from stereo image pairs using OpenCV. Anaglyphs are images designed to produce a 3D effect when viewed with color-filtered glasses (e.g., red-cyan glasses).

## Features

- **True Anaglyph**: A traditional red-cyan anaglyph using grayscale values for both the red and cyan channels.
- **Gray Anaglyph**: Similar to True Anaglyph, but with more emphasis on gray tones in the cyan channel.
- **Color Anaglyph**: Keeps the full color for the right eye (cyan) and uses red for the left eye.
- **Half Anaglyph**: A combination of grayscale red for the left eye and full color cyan for the right eye.
- **Optimized Anaglyph**: An optimized version designed for better color preservation.

## Prerequisites

- [OpenCV 4.x](https://opencv.org/) or higher.
- C++ compiler with OpenMP support.

## Compilation Instructions

Use the following commands to compile the program:

```bash
g++ anaglyphsCOPY.cpp -fopenmp `pkg-config opencv4 --cflags` -c
g++ anaglyphsCOPY.o -fopenmp `pkg-config opencv4 --libs` -lstdc++ -o anaglyphsCOPY
```

## How to Run

After compiling, you can run the program with one of the supported anaglyph types:

```bash
./anaglyphsCOPY "True Anaglyph"
./anaglyphsCOPY "Gray Anaglyph"
./anaglyphsCOPY "Color Anaglyph"
./anaglyphsCOPY "Half Anaglyph"
./anaglyphsCOPY "Optimized Anaglyph"
```

## Example

Make sure to have a stereo image named `stereo_image.jpg` in the working directory. The image should consist of two side-by-side views: the left image and the right image.

## Supported Anaglyph Types

- **True Anaglyph**: Uses grayscale for both left (red) and right (cyan).
- **Gray Anaglyph**: Applies grayscale for the left eye and cyan.
- **Color Anaglyph**: Left eye in red, right eye in full color.
- **Half Anaglyph**: Left eye in grayscale red, right eye in full color cyan.
- **Optimized Anaglyph**: Preserves more color while creating the anaglyph effect.

## Performance Measurement

The code tracks the time taken to create the anaglyph for multiple iterations and displays the total time, the time for one iteration, and iterations per second (IPS).
