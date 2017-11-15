#include <cstring>
#include <stdexcept>
#include <iostream>
#include "Matrix.h"


Matrix::Matrix() {
    m = 3;
    n = 3;
    makeEmpty();
}

Matrix::Matrix(unsigned int rows, unsigned int columns) {
    m = rows;
    n = columns;
    makeEmpty();
}

Matrix::Matrix(Matrix &matrixToCopy) {
    m = matrixToCopy.m;
    n = matrixToCopy.n;

    structure = new int *[m];

    for (int i = 0; i < m; i++) {
        structure[i] = new int[n];
        for (int j = 0; j < n; j++) {
            structure[i][j] = matrixToCopy.structure[i][j];
        }
    }
}

Matrix::Matrix(Matrix &&matrixToMove) {
    m = matrixToMove.m;
    n = matrixToMove.n;
    structure = matrixToMove.structure;

    matrixToMove.m = 0;
    matrixToMove.n = 0;
    matrixToMove.structure = nullptr;
}

Matrix::~Matrix() {
    for (int i = 0; i < m; i++) {
        delete structure[i];
    }

    delete structure;
}

void Matrix::setValue(unsigned int row, unsigned int column, int value) {
    structure[row][column] = value;
}

int Matrix::getValue(unsigned int row, unsigned int column) {
    return structure[row][column];
}

Matrix Matrix::add(Matrix matrixToAdd) {
    Matrix result(matrixToAdd.m, matrixToAdd.n);

    if (matrixToAdd.m != m || matrixToAdd.n != n) {
        throw std::invalid_argument("Matrix dimensions do not match!");
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result.structure[i][j] = structure[i][j] + matrixToAdd.structure[i][j];
        }
    }

    return result;
}

void Matrix::print() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << "[" << structure[i][j] << "]";
        }
        std::cout << std::endl;
    }
}

void Matrix::makeEmpty() {
    structure = new int *[m];

    for (int i = 0; i < m; i++) {
        structure[i] = new int[n];
        for (int j = 0; j < n; j++) {
            structure[i][j] = 0;
        }
    }
}

Matrix Matrix::multiply(int scalar) {
    Matrix result(*this);
    for (int i = 0; i < result.m; i++) {
        for (int j = 0; j < result.n; j++) {
            result.structure[i][j] *= scalar;
        }
    }
    return result;
}
