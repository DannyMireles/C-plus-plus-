#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main() {
  string filename;
  int width = 0;
  int height = 0;
  int originalWidth = 0;
  // int originalHeight = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  
  // get filename
  // cout << "Input filename: ";
  cin >> filename;
  
  // cout << "Input width and height: ";
  
  // check if fails after getting a value for width, height, targetWidth, and targetHeight that is not an integer or negative or 0
  cin >> width; 
  if (cin.fail()) {
	  cout << "Error: width is a non-integer value " << endl;
	  return -1;
  }
  if (width <= 0) {
	  cout << "Error: width must be greater than 0. You entered " << width;
	  return -1;
  }
  
  cin >> height; 
  if (cin.fail()) {
	  cout << "Error: height is a non-integer value " << endl;
	  return -1;
  }
  if (height <= 0) {
	  cout << "Error: height must be greater than 0. You entered " << height;
	  return -1;
  }
  
  cout << "Input target width and height: ";
  cin >> targetWidth;
  if (cin.fail()) {
	  cout << "Error: target width is a non-integer value " << endl;
	  return -1;
  }
  if (targetWidth <= 0) {
	  cout << "Error: target width must be greater than 0. You entered " << targetWidth;
	  return -1;
  }
    if (targetWidth > width) {
	  cout << "Error: target width must be less than width, " << targetWidth << " is greater than " << width;
	  return -1;
  }
  
  cin >> targetHeight;
  if (cin.fail()) {
	  cout << "Error: target height is a non-integer value " << endl;
	  return -1;
  }
  if (targetHeight <= 0) {
	  cout << "Error: target height must be greater than 0. You entered " << targetHeight;
	  return -1;
  }
  if (targetHeight > height) {
	  cout << "Error: target height must be less than height, " << targetHeight << " is greater than " << height;
	  return -1;
  }
  
  // save originalWidth since width will change with carving
  originalWidth = width; 
  // save originalHeight since height will change with carving
  // originalHeight = height;
  
  Pixel** image1 = createImage(width, height);
  if (image1 != nullptr) { // new returns nullptr if it fails to allocate array
  
    if (loadImage(filename, image1, width, height)) {
      
      // uncomment for part 2
      
      while ((width - targetWidth > 0) || (height - targetHeight > 0)) {
        if (width - targetWidth > 0) {
          int* verticalSeam = findMinVerticalSeam(image1, width, height);
          removeVerticalSeam(image1, width, height, verticalSeam);
          deleteSeam(verticalSeam);
          width--;
        }
        
		
        // this is for the extra credit
        if (height - targetHeight > 0) {
          int* horizontalSeam = findMinHorizontalSeam(image1, width, height);
          removeHorizontalSeam(image1, width, height, horizontalSeam);
          deleteSeam(horizontalSeam);
          height--;
        }
		
      }
      
      
      stringstream ss;
      ss << "carved" << width << "X" << height << "." << filename;
      outputImage(ss.str().c_str(), image1, width, height);
    }
  }
  
  // call last to remove the memory from the heap
  deleteImage(image1, originalWidth);
}