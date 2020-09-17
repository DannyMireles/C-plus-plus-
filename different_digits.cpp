#include <iostream>
#include "functions.h"
using std::cout, std::cin, std::endl;

int main() {
	int a;
	int b;
	// ask for input
	cout << "Enter numbers 0 < a <= b <= 10000: ";
	cin >> a;
	cin >> b;
	
	// check to see if numbers inputted are in valid range
	if (is_valid_range(a, b) == false) {
		 cout << "Invalid input" << endl; 
	 } else {
		 cout << "There are " << count_valid_numbers(a, b) << " valid numbers between " << a << " and " << b << endl;
	 }	
}