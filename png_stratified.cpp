/*
    Adapted from LodePNG Examples

    Look at examples here for more usecases: https://github.com/lvandeve/lodepng/tree/master/examples
*/

#include "lib/lodepng.h"
#include <iostream>
#include <vector>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
#include <random>

using namespace std;

int main() {
    unsigned width, height;
    const char* filename = "im/oldHouseSquare.png";
    vector<unsigned char> image;   // store pixels

    // decode image
    unsigned error = lodepng::decode(image, width, height, filename);
    if(error) cout << "decoder error " << error << ": " << lodepng_error_text(error) << endl;

    unsigned int array2D[width][height];

    unsigned int sum = 0;


    //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBA RGBA...
    cout <<  width << " " << height <<  " " << image.size() << " " << filename << endl;

    // manipulate the image (in this case, remove red and blue channels, only keep green channel)
    for(unsigned y = 0; y < height; y++)
        for(unsigned x = 0; x < width; x++) {
        	array2D[x][y] = image[4 * width * y + 4 * x + 0];

        	array2D[x][y] = 255 - array2D[x][y];

        	sum += array2D[x][y];

            image[4 * width * y + 4 * x + 0] = 255;
            image[4 * width * y + 4 * x + 1] = 255;
            image[4 * width * y + 4 * x + 2] = 255;
            image[4 * width * y + 4 * x + 3] = 255;
        }
    
    vector<double> rowStacked;

    vector<double> columns[width];
    double colSums[width];

    double colSumForRow = 0.0;
    double rowSumForCol = 0.0;

	// Calculate for each row
    for(unsigned x = 0; x < width; x++){
    	colSums[x] = 0.0;
    	for(unsigned y = 0; y < height; y++){
    		colSumForRow += array2D[x][y];
    		colSums[x] += array2D[x][y];
    	}
    	rowStacked.push_back(double(colSumForRow/sum));
    }

	// Calculate for each column
    for(unsigned x = 0; x < width; x++){
    	rowSumForCol = 0.0;
    	for(unsigned y = 0; y < height; y++){
    		rowSumForCol += array2D[x][y];
    		columns[x].push_back(double(rowSumForCol)/colSums[x]);
    	}
    }


    srand(time(NULL));

    //Create Grid
    unsigned ratio = 1;
    double grid = height / ratio;

    int interval = (RAND_MAX)/grid;

    unsigned total = 0;

    for(unsigned i = 0; i < width/ratio; i++){
        for(unsigned j = 0; j < height/ratio; j++){

			// Uniform random for each grid cell
            double r1 = double(rand() % interval + double((i)*interval+1.0)) / (double(RAND_MAX)+1.0);
            double r2 = double(rand() % interval + double((j)*interval+1.0)) / (double(RAND_MAX)+1.0);

			// Sample
    	    int row = lower_bound(rowStacked.begin(), rowStacked.end(), r1) - rowStacked.begin();
    	    int col = lower_bound(columns[row].begin(), columns[row].end(), r2) - columns[row].begin();

    	    image[4 * width * col + 4 * row + 0] = 0;
     	    image[4 * width * col + 4 * row + 1] = 0;
            image[4 * width * col + 4 * row + 2] = 0;
            image[4 * width * col + 4 * row + 3] = 255;

            total++;
        }
   	}

    cout << total << endl;
 

    // encode the modified image
    const char* output_filename = "im/oldHouseStratFinal.png";
    error = lodepng::encode(output_filename, image, width, height);

    return 0;
}