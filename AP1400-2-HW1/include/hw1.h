#ifndef AP_HW1_H
#define AP_HW1_H
#include<vector>
#include<iostream>
#include<random>
using Matrix = std::vector<std::vector<double>>;
namespace algebra
{
    //zeros implement this function so that it will create a n x m matrix with all elements equal to zero.
    Matrix zeros(size_t n, size_t m);
    //ones implement this function so that it will create a n x m matrix with all elements equal to one.
    Matrix ones(size_t n, size_t m);
    //random implement this function so that it will create a n x m matrix with all elements a random number between min and max.
    Matrix random(size_t n, size_t m, double min, double max);
    //show implement this function so that it will display the matrix in a beautiful way.
    void show(const Matrix& matrix);
    //implement this function so that it multiplies the matrix into the constant scalar c.
    Matrix multiply(const Matrix& matrix, double c);
    //implement this function so that it multiplies the matrix1 into matrix2. (this is not an element-wise multiplication)
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);
    //implement this function so that it adds the constant number c to every element of matrix.
    Matrix sum(const Matrix& matrix, double c);
    //implement this function so that it adds 2 matrices to each other.
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);
    //transpose implement this function so that it will generate the transpose matrix of the input matrix.
    Matrix transpose(const Matrix& matrix);
    //minor implement this function so that it will create the minor of the input matrix with respect to nth row and mth column.
    Matrix minor(const Matrix& matrix, size_t n, size_t m);
    //determinant implement this function so that it calculates the determinant of the input matrix.
    double determinant(const Matrix& matrix);
    //inverse implement this function so that it generates the matrix's inverse.
    Matrix inverse(const Matrix& matrix);
    //concatenate implement this function so that it will concatenate matrix1 and matrix2 along the specified axis. (axis=0: on top of each other | axis=1: alongside each other).
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0);
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);
}

#endif //AP_HW1_H
