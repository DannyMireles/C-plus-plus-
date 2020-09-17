#include <iostream>
#include <stdexcept>
#include "picture_hanging.h"

#define TODO(X) cout << "[TODO] " << __FUNCTION__ << ": " << X << endl;

using std::cout, std::endl;
using std::ostream;
using std::out_of_range;

/*
make a copy of src (elements 0..len-1)
*/
int* copy(const int src[], const size_t len) {
	int* array_copy = new int[len];
	for (unsigned int i = 0; i < len; ++i) {
		array_copy[i] = src[i];
	}
    return array_copy;
}

/*
return i such that A[i] = key, or -1 if key is not in A
*/
int find(const int A[], const size_t len, const int key) {
    for (unsigned int i = 0; i < len; ++i) {
		if (A[i] == key) {
			return i;
		}
		else {
			return -1;
		}
	}
}

/*
remove the specified number (cnt) of elements starting at specified index (idx)
*/
void remove(int A[], size_t& len, const size_t idx, const size_t cnt) {
    if (len < (idx  + cnt)) {
		throw out_of_range("Error: removing too many elements");
	} 
	for (unsigned int i = 0; i < (len - idx  - cnt); ++i) {
		A[i + idx] = A[i + cnt + idx];
	}
	for (unsigned int i = (len-cnt); i < len; ++i) {
		A[i] = 0;
	}
	len = (len-cnt);
}

/*
remove all instances of duplicate values in A (including opposites, so 1 and -1 are the same)
*/
void removeDuplicates(int A[], size_t& len) {
	unsigned int new_len = 1;
    for (unsigned int i = 0; i < len; ++i) {
		for (unsigned int j = 0; j < new_len; ++i) {
			if (A[i] == A[j]) {
				i = 0;
			}
			if (j == new_len) {
				A[new_len++] = A[i];
			}
		}
	}
}

/*
returns true if str is not reducible (no canceling neighbors)
*/
bool isStable(const int A[], const size_t len) {
    unsigned int new_len = 1;
    for (unsigned int i = 0; i < len-1; ++i) {
		for (unsigned int j = 0; j < new_len; ++i) {
			if (A[i] == A[j]) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}

/*
remove all instances of value
*/
void removeAll(int A[], size_t& len, const int value) {
    for (unsigned int i = 0; i < len-1; ++i) {
		A[value] = 0;
	}
}

/*
repeatedly remove any pair of neighbors which are opposites (e.g. 1 and -1).
*/
void reduce(int A[], size_t& len) {
	unsigned int i = 0;
     for (i = 0; i < len-1; ++i) {
		 int next = i+1;
		 if (A[i] == A[next]) {
			 A[i] = 0;
			 A[next] = 0;
		 }
	 } 
}

/*
return true if removing any single value (and it's opposite, e.g. 1 and -1) reduces the sequence to empty.
*/
bool isCorrect(const int A[], const size_t len) {
	return false;
}
