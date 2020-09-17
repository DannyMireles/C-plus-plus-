#include "functions.h"

bool is_valid_range(int a, int b) {
	if((a > 0) && (a <= b) && (b <= 10000)) {
		return true;
	} else {
		return false;
	}	
}	
// This function returns the boolean value true if and
// only if inputs a and b satisfy the constraint that 0 < a <= b <= 10000.

int count_digit_occurrences(int number, int digit) {
		int count = 0;
		int remainder = 0;
		while(number > 0)  {
			remainder = (number % 10);
			if (remainder == digit) {
				count++;
			}
			number /= 10;
		}
		return count;
	}
// This function returns how many times
// digit occurs in number, where  0 <= digit <= 9. 

bool has_repeated_digits(int number) {
	int remainder = number;
	int value = number;
	int count = 0;
	while(value > 0) {
		remainder = value % 10;
		count = count_digit_occurrences(number, remainder);
		if (count > 1) {
			return true;
		}
		value /= 10;
	}
	return false;
}
// This function returns the boolean value 
// true if and only if number contains repeated digits.  

int count_valid_numbers(int a, int b) {
	int count = 0;
	for(int i = a; i <= b ; i++) {
		if(!has_repeated_digits(i)) {
		count++;
		}
	}
	return count;
}
// This function returns how many numbers in the range [a, b] 
// (i.e. a <= number <= b) are valid according to the queen’s superstition, i.e. how many numbers do not contain repeated digits, where 0 < a <= b <= 10000 (i.e. [a,b] is a valid range).
