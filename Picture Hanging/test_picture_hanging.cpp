#include <iostream>
#include <stdexcept>
#include "picture_hanging.h"

#define EXPECT_EQ(X,Y) if(X!=Y){explain_eq(#X,X,#Y,Y,__FUNCTION__,__LINE__);pass=false;}

#define ASSERT_EQ(X,Y) if(X!=Y){explain_eq(#X,X,#Y,Y,__FUNCTION__,__LINE__);return false;}

#define EXPECT_NE(X,Y) if(X==Y){explain_ne(#X,X,#Y,Y,__FUNCTION__,__LINE__);pass=false;}

#define ASSERT_NE(X,Y) if(X==Y){explain_ne(#X,X,#Y,Y,__FUNCTION__,__LINE__);return false;}

#define EXPECT_TRUE(X) if(!(X)){explain_tf(#X,X,true,__FUNCTION__,__LINE__);pass=false;}

#define ASSERT_TRUE(X) if(!(X)){explain_tf(#X,X,true,__FUNCTION__,__LINE__);return false;}

#define EXPECT_FALSE(X) if(X){explain_tf(#X,X,false,__FUNCTION__,__LINE__);pass=false;}

#define ASSERT_FALSE(X) if(X){explain_tf(#X,X,false,__FUNCTION__,__LINE__);return false;}

using std::cout, std::endl;
using std::ostream;
using std::runtime_error;

ostream& operator<<(ostream& os, std::nullptr_t) {
    os << "nullptr";
    return os;
}

template <typename T>
void explain_eq(const char n1[], const T& o1, const char n2[], const T& o2, const char func[], const size_t line) {
    cout << func << ":" << line << ": Failure" << endl;
    cout << "Expected equality of these values:" << endl;
    cout << "  " << n1 << endl;
    cout << "    Which is: " << o1 << endl;
    cout << "  " << n2 << endl;
    cout << "    Which is: " << o2 << endl;    
}

template <typename T1, typename T2>
void explain_ne(const char n1[], const T1& o1, const char n2[], const T2& o2, const char func[], const size_t line) {
    cout << func << ":" << line << ": Failure" << endl;
    cout << "Expected inequality of these values:" << endl;
    cout << "  " << n1 << endl;
    cout << "    Which is: " << o1 << endl;
    cout << "  " << n2 << endl;
    cout << "    Which is: " << o2 << endl;    
}

void explain_tf(const char name[], bool actual, bool expected, const char func[], const size_t line) {
    cout << func << ":" << line << ": Failure" << endl;
    cout << "Value of " << name << endl;
    cout << "    Actual: " << actual << endl;
    cout << "  Expected: " << expected << endl;    
}

bool test_copy() {
    bool pass = true;
    
    {
        int A[] = {1,2,3,4,5};
        size_t len = sizeof(A)/sizeof(int);
        int* actual = copy(A, len);
        int expected[] = {1,2,3,4,5};
        size_t expected_len = sizeof(expected)/sizeof(int);
        ASSERT_NE(actual, nullptr);
        for (size_t i = 0; i < expected_len; ++i) {
            EXPECT_EQ(actual[i], expected[i]);
        }
        delete[] actual;
    }
    
    return pass;
}

bool test_find() {
    bool pass = true;
    
    {
        int A[] = {1,2,3,4,5};
        size_t len = sizeof(A)/sizeof(int);
        int key = 3;
        int expected = 2;
        int actual = find(A, len, key);
        EXPECT_EQ(actual, expected);
    }
    
    return pass;
}

bool test_remove() {
    bool pass = true;
    
    {
        int A[] = {1,2,3,4,5};
        size_t len = sizeof(A)/sizeof(int);
        remove(A, len, 2, 2);
        int expected[] = {1,2,5};
        size_t expected_len = sizeof(expected)/sizeof(int);
        int* actual = A;
        size_t actual_len = len;
        ASSERT_EQ(actual_len, expected_len);
        for (size_t i = 0; i < actual_len; ++i) {
            EXPECT_EQ(actual[i], expected[i]);
        }
    }
    
    return pass;
}

bool test_removeDuplicates() {
    bool pass = true;
    
    {
        int A[] = {1,2,-1,3,1,4,-1,5,1,-1,5};
        size_t len = sizeof(A)/sizeof(int);
        int expected[] = {1,2,3,4,5};
        size_t expected_len = sizeof(expected)/sizeof(int);
        removeDuplicates(A, len);
        int* actual = A;
        size_t actual_len = len;
        ASSERT_EQ(actual_len, expected_len);
        for (size_t i = 0; i < actual_len; ++i) {
            EXPECT_EQ(actual[i], expected[i]);
        }
    }
    
    return pass;
}


bool test_isStable() {
    bool pass = true;
    
    {
        int A[] = {1,2,3,4,5};
        size_t len = sizeof(A)/sizeof(int);
        EXPECT_TRUE(isStable(A, len));
    }
    
    return pass;
}

bool test_removeAll() {
    bool pass = true;

    {
        int A[] = {1,2,-1,3,1,4,-1,5,1,-1};
        size_t len = sizeof(A)/sizeof(int);
        int expected[] = {2,-1,3,4,-1,5,-1};
        size_t expected_len = sizeof(expected)/sizeof(int);
        removeAll(A, len, 1);
        int* actual = A;
        size_t actual_len = len;
        ASSERT_EQ(actual_len, expected_len);
        for (size_t i = 0; i < actual_len; ++i) {
            EXPECT_EQ(actual[i], expected[i]);
        }
    }
    
    return pass;
}

bool test_reduce() {
    bool pass = true;

    {
        int A[] = {1,2,3,-3,4,5};
        size_t len = sizeof(A)/sizeof(int);
        int expected[] = {1,2,4,5};
        size_t expected_len = sizeof(expected)/sizeof(int);
        reduce(A, len);
        int* actual = A;
        size_t actual_len = len;
        ASSERT_EQ(actual_len, expected_len);
        for (size_t i = 0; i < actual_len; ++i) {
            EXPECT_EQ(actual[i], expected[i]);
        }
    }

    return pass;
}

bool test_isCorrect() {
    bool pass = true;
    
    {
        int A[] = {1,2,3,4,5};
        size_t len = sizeof(A)/sizeof(int);
        EXPECT_FALSE(isCorrect(A, len));
    }
    
    return pass;
}

int main() {
    bool pass = true;
    
    pass &= test_copy();
    pass &= test_find();
    pass &= test_remove();
    pass &= test_removeDuplicates();
    pass &= test_isStable();
    pass &= test_removeAll();
    pass &= test_reduce();
    pass &= test_isCorrect();
    
    if (pass) {
        cout << "ALL TESTS PASSED" << endl;
    }

    return !pass;
}