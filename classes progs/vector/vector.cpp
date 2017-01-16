#include "vector.h"

// constructors + destructor
Vector::Vector(){
    buffer = 10;
    length = 10;
    ptr = new int[length];
}

Vector::Vector(const int size){
    buffer = size;
    length = size;
    ptr = new int[length];
}

Vector::Vector(const int* arr, const int size){
    buffer = size;
    length = size;
    ptr = new int[length];
    for(std::ptrdiff_t i = 0; i < length; i++){
        ptr[i] = arr[i];
    }
}

Vector::~Vector(){
    delete [] ptr;
}

Vector::Vector(const Vector& v){ // copy
    copyOrWat(v);
}

void Vector::copyOrWat(const Vector& v){
    length = v.length;
    ptr = new int[length];
    for(std::ptrdiff_t i = 0; i < length; i++){
        ptr[i] = v.ptr[i];
    }
}

// overrided operators
Vector& Vector::operator= (const Vector& v){
    copyOrWat(v);
    return *this;
}

int Vector::operator[] (const int ind) const{
    return ptr[ind];
}

int& Vector::operator[] (const int ind){
    return ptr[ind];
}

bool Vector::operator== (const Vector& v) const{
    if (length != v.length) return false;
    for (std::ptrdiff_t i = 0; i < length; i++){
        if(ptr[i] != v.ptr[i]) return false;
    }
    return true;
}

bool Vector::operator!= (const Vector& v) const {
    return(!operator==(v));
}

// vector methods
void Vector::append(const int elem){
    if(length + 1 >= buffer){
        buffer = length * 2;
    }
    int * temp_ptr = new int[length];
    for (std::ptrdiff_t i =  0; i < length; i++){
        temp_ptr[i] = ptr[i];
    }
    delete [] ptr; // free before new
    ptr = new int[buffer];
    int ind = 0;
    for (std::ptrdiff_t i =  0; i < length; i++){
        ptr[i] = temp_ptr[i];
        ind = i;
    }
    ptr[ind + 1] = elem;
    length += 1;
    delete [] temp_ptr;
}

void Vector::remove(const int ind){
    length -= 1;
    int * temp_ptr = new int[length];
    int flag = 0;
    for(std::ptrdiff_t i = 0; i < length; i++){
        if(i == ind - 1){
            flag = 1;
        }
        if (flag == 0){
            temp_ptr[i] = ptr[i];
        } else {
            temp_ptr[i] = ptr[i + 1];
        }
    }
    delete [] ptr;
    ptr = new int[length];
    for (std::ptrdiff_t i = 0; i < length; i++){
        ptr[i] = temp_ptr[i];
    }

    delete [] temp_ptr;
}

// other methods
std::string Vector::toString() const {
    std::string str = "";
    str += "[";
    for(std::ptrdiff_t i = 0; i < length; i++){
        str += std::to_string(*(ptr + i));
        str += " ";
    }
    str += "]";
    return str;
}

int Vector::len() const {
    return length;
}