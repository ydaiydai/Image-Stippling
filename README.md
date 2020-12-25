# Image Stippling
 Image Stippling in C++

## Summary
This is an Image Stippling work I made which I am proud of when I was learning offline rendering. It creates a stippling image from an arbitrary image in C++. Two different mappings were implemented, one uses pure 2D random uniform seuqences and the other one uses 2D stratified sequences. 

## Additional Information
It uses LodePNG library for PNG encoding and decoding. 

## Compiling in C++
If you have a hypothetical your_program.cpp that #includes and uses lodepng.h, you can build as follows:
* For Uniform Sampling: `$ g++ -std=c++11 -o png_uniform.cpp lib/lodepng.cpp -Wall -Wextra -pedantic -ansi -O3` 
or
* For Stratified Sampling: `$ g++ -std=c++11 -o png_stratified.cpp lib/lodepng.cpp -Wall -Wextra -pedantic -ansi -O3` 


