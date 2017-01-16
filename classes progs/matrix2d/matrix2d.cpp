#include "matrix2d.h"

// constuctors + destructor
Matrix2d::Matrix2d(){
    cols = 0;
    rows = 0;
    matrix = new int[cols * rows];
}

Matrix2d::Matrix2d(const int size){
    cols = rows = size;
    matrix = new int[cols*rows];
    initWithNulls();
}

Matrix2d::Matrix2d(const int cols_, const int rows_){
    cols = cols_;
    rows = rows_;
    matrix = new int[cols*rows];
    initWithNulls();
}

Matrix2d::Matrix2d(const int * array, const int cols_, const int rows_){
    cols = cols_;
    rows = rows_;
    matrix = new int[cols*rows];
    for (std::ptrdiff_t i = 0; i < cols*rows; i++){
        matrix[i] = array[i];
    }
}

Matrix2d::~Matrix2d(){
    delete [] matrix;
}

Matrix2d::Matrix2d(const Matrix2d& m){
    cols = m.cols;
    rows = m.rows;
    matrix = new int[cols * rows];
    copyOrWat(m);
}

void Matrix2d::copyOrWat(const Matrix2d& m){
    for (std::ptrdiff_t i = 0; i < rows*cols; i++){
        matrix[i] = m.matrix[i];
    }
}


// overrided operators
Matrix2d Matrix2d::operator= (const Matrix2d& m){
    cols = m.cols;
    rows = m.rows;
    matrix = new int[cols * rows];
    copyOrWat(m);
    return Matrix2d(matrix, cols, rows);
}

bool Matrix2d::operator== (const Matrix2d& m) const{
    for (std::ptrdiff_t i = 0; i < cols*rows; i++){
        if (matrix[i] != m.matrix[i]){
            return false;
        }
    }
    return true;
}

bool Matrix2d::operator!= (const Matrix2d& m) const{
    return (!operator==(m));
}

// other methods
void Matrix2d::serialize(std::ostream& ostrm) {
    ostrm.put(cols);
    ostrm.put(rows);
    for (std::ptrdiff_t i = 0; i < rows*cols; i += 1){
        ostrm.put(matrix[i]);
    }
    // ostrm.write(matrix, rows*cols);
}

void Matrix2d::deserialize(std::istream& istrm){
    cols = istrm.get();
    rows = istrm.get();
    for (std::ptrdiff_t i = 0; i < cols*rows; i += 1){
        matrix[i] = istrm.get();
    }
}

void Matrix2d::initWithNulls(){
    for(std::ptrdiff_t i = 0; i < rows*cols; i++){
        matrix[i] = 0;
    }
}

std::ostream& Matrix2d::writeTo(std::ostream& ostrm) const{
    for (std::ptrdiff_t i = 0; i < rows; i++){
        for (std::ptrdiff_t j = 0; j < cols; j++){
            ostrm << matrix[i*cols + j];
        }
        ostrm << std::endl;
    }
    return ostrm;
}