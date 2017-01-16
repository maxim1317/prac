#ifndef HG_VECTOR_H
#define HG_VECTOR_H

// #include <iostream>
#include <string>

class Vector {
public:
    // constructors + destructor
    Vector();
    Vector(const int size);
    Vector(const int* arr, const int size);
    ~Vector();
    Vector(const Vector& v);

    // overrided operators
    Vector& operator= (const Vector& v);
    int operator[] (const int ind) const;
    int& operator[] (const int ind);
    bool operator== (const Vector& v) const;
    bool operator!= (const Vector& v) const;

    //vector methods
    void append(const int elem);
    void remove(const int ind);

    // other methods
    std::string toString() const;
    int len() const;
private:
    int buffer = 0;
    int length = 0;
    int *ptr = nullptr;

    void copyOrWat(const Vector& v); // for copy-constructor & operator=
};

#endif