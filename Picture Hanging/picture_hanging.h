#ifndef PICTURE_HANGING_H
#define PICTURE_HANGING_H

#include <iostream>

/*
helper function to pretty print an array
*/
template <typename T>
void print_array(const T A[], const size_t len, std::ostream& os) {
    os << "[";
    if (len > 0) {
        os << A[0];
    }
    for (size_t i = 1; i < len; ++i) {
        os << ", " << A[i];
    }
    os << "]";
}

/*
make a copy of src (elements 0..len-1)
*/
int* copy(const int src[], const size_t len);

/*
return i such that A[i] = key, or -1 if key is not in A
*/
int find(const int A[], const size_t len, const int key);

/*
remove the specified number (cnt) of elements starting at specified index (idx)
*/
void remove(int A[], size_t& len, const size_t idx, const size_t cnt);

/*
remove all instances of duplicate values in A (including opposites, so 1 and -1 are the same)
*/
void removeDuplicates(int A[], size_t& len);

/*
returns true if sequence (A) is not reducible (no canceling neighbors)
*/
bool isStable(const int A[], const size_t len);

/*
remove all instances of value
*/
void removeAll(int A[], size_t& len, const int value);

/*
repeatedly removes any pair of neighbors which are opposites (e.g. 1 and -1).
*/
void reduce(int A[], size_t& len);

/*
return true if removing all instances of any value (and it's opposite, e.g. 1 and -1) causes the sequence to reduce to empty.
*/
bool isCorrect(const int A[], const size_t len);

#endif
