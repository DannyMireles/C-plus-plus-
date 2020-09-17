#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  // cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // delete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  // cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  // cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
	  delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
	int* array = new(nothrow) int[length];
	for (int i = 0; i < length; i++) { 
		array[i] = 0; 	 //all elements in array have value 0
	}	
  return array;
}

void deleteSeam(int* seam) {
	// seam would be array in the function createSeam
	delete[] seam;
	seam = nullptr;
	// no return needed because it is void
}

bool loadImage(string filename, Pixel** image, int width, int height) {

	ifstream ifs (filename);
  
	//check if opened
	if (!ifs.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    return false;
	}
  
	// get type from preamble
	char type[3];
	ifs >> skipws >> type; // should be P3
	if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
		cout << "Error: type is " << type << " instead of P3" << endl;
		return false;
	}
  
	// get width (w) and height (h) from preamble
	int w = 0, h = 0;
	ifs >> skipws >> w;
	if (ifs.fail()) {
		ifs.clear();
		ifs.ignore(255, '\n');
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	
	// now check width 
	if (w != width) { 
		cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl; 
		return false;
	}
  
	ifs >> skipws >> h;
	if (ifs.fail()) {
		ifs.clear();
		ifs.ignore(255, '\n');
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	
	//now check height (output message if not)
	if (h != height) { 
		cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl; 
		return false;
	}
  
	// check if colorMax is in range
	int colorMax = 0;
	ifs >> skipws >> colorMax;
	if (ifs.fail()) {
		ifs.clear();
		ifs.ignore(255, '\n');
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if (colorMax != 255) {
		cout << "Error: file is not using RGB color values." << endl;
		return false;
	}
  
	// get RGB values
	int Counter = 0;
	Pixel p;
	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {  //ransverse through entire array
			ifs >> skipws >> p.r;
			if (ifs.fail()) {
				if (ifs.eof()) {
					cout << "Error: not enough color values" << endl;
					return false;
				} 
				ifs.clear();
				ifs.ignore(255, '\n');
				cout << "Error: read non-integer value" << endl;
				return false;
			}
			if (p.r < 0 || p.r > 255) {
				cout << "Error: invalid color value " << p.r << endl;
				return false;
			}
			Counter++;
		  
			ifs >> skipws >> p.g;
			if (ifs.fail()) {
				if (ifs.eof()) {
					cout << "Error: not enough color values" << endl;
					return false;
				} 
				ifs.clear();
				ifs.ignore(255, '\n');
				cout << "Error: read non-integer value" << endl;
				return false;
			}
			if (p.g < 0 || p.g > 255) {
				cout << "Error: invalid color value " << p.g << endl;
				return false;
			}
			Counter++;	
			
			ifs >> skipws >> p.b;
			if (ifs.fail()) {
				if (ifs.eof()) {
					cout << "Error: not enough color values" << endl;
					return false;
				} 
				ifs.clear();
				ifs.ignore(255, '\n');
				cout << "Error: read non-integer value" << endl;
				return false;
			}
			if (p.b < 0 || p.b > 255) {
				cout << "Error: invalid color value " << p.b << endl;
				return false;
			}	
			
			Counter++;
		  
			image[w][h] = p;
		}
	}
	
	//finally, check if there are too many values
	int too_many = 0;
	ifs >> too_many;
	if (!(ifs.fail())) {
		cout << "Error: too many color values" << endl;
		return false;
	}
	return true;
}


bool outputImage(string filename, Pixel** image, int width, int height) {
	ofstream ofs(filename);
    // check if output stream opened successfully
	if (ofs.is_open()) {
		// output preamble
		ofs << "P3" << endl;
		ofs << width << endl;
		ofs << height << endl;
		ofs << 255 << endl;
		
		
		// output image 
		Pixel pix;
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				pix = image[w][h];
				ofs << pix.r << endl;
				ofs << pix.g << endl;
				ofs << pix.b << endl;
			}
		}
	
	
	} else {
		cout << "Error: failed to open output file " << filename << endl;
	}

return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
	int xRight = x + 1;
	int xLeft = x - 1;
	int yUp = y + 1;
	int yDown = y - 1;
	
	if (x == 0) {
		xLeft = width - 1;
	}
	else if (x == width - 1) {
		xRight = 0;
	}
	if (y == 0) {
		yDown = height - 1;
	}
	else if (y == height - 1) {
		yUp = 0;
	}
	
	int energyValXR = image[xLeft][y].r - image[xRight][y].r; 
	int energyValXG = image[xLeft][y].g - image[xRight][y].g; 
	int energyValXB = image[xLeft][y].b - image[xRight][y].b;
	
	int energyValX = (energyValXR * energyValXR + energyValXG * energyValXG + energyValXB * energyValXB);
	
	int energyValYR = image[x][yDown].r - image[x][yUp].r; 
	int energyValYG = image[x][yDown].g - image[x][yUp].g; 
	int energyValYB = image[x][yDown].b - image[x][yUp].b;
	
	int energyValY = (energyValYR * energyValYR + energyValYG * energyValYG + energyValYB * energyValYB);
	
	int totalEnergy = energyValX + energyValY;
	
	return totalEnergy;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
	int start_row = 0;
	int curr_energy = 0;
	int total_energy = 0;
	total_energy = energy(image, start_col, start_row, width, height);
	
	int new_col = start_col;
	int left = 0;
	int forward = 0;
	int right = 0;
	
	seam[0] = start_col; // set seam for the first row to the starting column (this is our first pixel)
	
	for (int i = 1; i < height; ++i) { //transverse throught all rows 
			
		int go_left = new_col + 1;
		int go_forward = new_col;
		int go_right = new_col - 1;
		
		// check the different possinilities. Middle is always the preferred option in a tie.
		if (new_col == 0) {
			forward = energy(image, go_forward, i, width, height);
			left = energy(image, go_left, i, width, height);
			right = forward;
		}
		else if (new_col == width - 1) {
			right = energy(image, go_right, i, width, height);
			forward = energy(image, go_forward, i, width, height);
			left = forward;
		} 
		else {
			left = energy(image, go_left, i, width, height);
			forward = energy(image, go_forward, i, width, height);
			right = energy(image, go_right, i, width, height);
		}
		
		
		if (right < forward && right < left) { // when energy to right is least
			seam[i] = go_right;
			curr_energy = right;
			new_col = go_right;
		}
		else if (left < forward || (left == right && left < forward)) { // when the energy to the left is the least or tied with right
			seam[i] = go_left;
			curr_energy = left;
			new_col = go_left;
		}
		else if (left == forward && right == forward) { // when there is a three-way tie, go forward
			seam[i] = go_forward;
			curr_energy = forward;
			new_col = go_forward;
		}
		else { // always default to middle
			seam[i] = go_forward;
			curr_energy = forward;
			new_col = go_forward;
		}
		
		total_energy += curr_energy;
	}
 return total_energy;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
	int start_col = 0;
	int curr_energy = 0;
	int total_energy = 0;
	total_energy = energy(image, start_col, start_row, width, height);
	
	int new_row = start_row;
	int left = 0;
	int forward = 0;
	int right = 0;
	
	seam[0] = start_row; // set seam for the first row to the starting column (this is our first pixel)
	
	for (int i = 1; i < width; ++i) { //transverse throught all rows 
			
		int go_left = new_row + 1;
		int go_forward = new_row;
		int go_right = new_row - 1;
		
		// check the different possinilities. Middle is always the preferred option in a tie.
		if (new_row == 0) {
			forward = energy(image, i, go_forward, width, height);
			left = energy(image, i, go_left, width, height);
			right = forward; 
		}
		else if (new_row == height - 1) {
			right = energy(image, i, go_right, width, height);
			forward = energy(image, i, go_forward, width, height);
			left = forward;
		} 
		else {
			left = energy(image, i, go_left, width, height);
			forward = energy(image, i, go_forward, width, height);
			right = energy(image, i, go_forward, width, height);
		}
		
		
		if (right < forward && right < left) { // when energy to right is least
			seam[i] = go_right;
			curr_energy = right;
			new_row = go_right;
		}
		else if (left < forward || (left == right && left < forward)) { // when the energy to the left is the least or tied with right
			seam[i] = go_left;
			curr_energy = left;
			new_row = go_left;
		}
		else if (left == forward && right == forward) { // when there is a three-way tie, go forward
			seam[i] = go_forward;
			curr_energy = forward;
			new_row = go_forward;
		}
		else { // always default to middle
			seam[i] = go_forward;
			curr_energy = forward;
			new_row = go_forward;
		}
		
		total_energy += curr_energy;
	}
 return total_energy;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
	
	int* min_seam = nullptr;
	int* curr_seam = nullptr;
	
	min_seam = createSeam(height);
	curr_seam = createSeam(height);
	
	int min_energy = loadVerticalSeam(image, 0, width, height, min_seam); //Set minimal energy to the result of loading the seam for the first column (ie start_col = 0)
	int curr_energy = 0;
	
	for (int i = 1; i < width; i++) {
		curr_energy = loadVerticalSeam(image, i, width, height, curr_seam);
		if (curr_energy < min_energy) {
			min_energy = curr_energy;
			for (int j = 0; j < height; j++) {
				min_seam[j] = curr_seam[j];
			}
		}
	}
	deleteSeam(curr_seam);
	return min_seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
	
	int* min_seam = nullptr;
	int* curr_seam = nullptr;
	
	min_seam = createSeam(width);
	curr_seam = createSeam(width);
	
	int min_energy = loadHorizontalSeam(image, 0, width, height, min_seam); //Set minimal energy to the result of loading the seam for the first column (ie start_col = 0)
	int curr_energy = 0;
	
	for (int i = 1; i < height; i++) {
		curr_energy = loadVerticalSeam(image, i, width, height, curr_seam);
		if (curr_energy < min_energy) {
			min_energy = curr_energy;
			for (int j = 0; j < width; j++) {
				min_seam[j] = curr_seam[j];
			}
		}
	}
	deleteSeam(curr_seam);
	return min_seam;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
	// For each row Remove pixel (seam[row], row) - note that seam[row] will be the column.
	// While width is greater than target width or height is greater than target height
	// If width is greater than target width
	// Find minimal vertical seam
	// Remove minimal vertical seam
	// Update width (i.e. decrement by one)
	// If height is greater than target height
	// Find minimal horizontal
	// Remove minimal horizontal seam
	// Update height (i.e. decrement by one)
	
	for (int h = 0; h < height; ++h) {
		for (int w = verticalSeam[h]; w < width-1; ++w) {
			image[w][h] = image[w+1][h];
		}
	}
}


void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
	for (int w = 0; w < width; ++w) {
		for (int h = horizontalSeam[w]; h < height - 1; ++h) {
			image[w][h] = image[w][h+1];
		}
	}
}



