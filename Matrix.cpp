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
    validate(row, column);
    structure[row][column] = value;
}

int Matrix::getValue(unsigned int row, unsigned int column) {
    validate(row, column);
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

Matrix Matrix::multiply(int scalar) {
    Matrix result(*this);
    for (int i = 0; i < result.m; i++) {
        for (int j = 0; j < result.n; j++) {
            result.structure[i][j] *= scalar;
        }
    }
    return result;
}

Matrix Matrix::multiply(Matrix otherMatrix) {
    if (this->getColumns() != otherMatrix.getRows()) {
        throw std::invalid_argument
                ("Matrix dimensions do not match; for A x B, A's columns count must match B's rows count");
    }
    Matrix result(this->getRows(),otherMatrix.getColumns());

    for (int i = 0; i < result.m; i++) {
        for (int j = 0; j < result.n; j++) {
            for (int r = 0; r < otherMatrix.m; r++) {
                result.structure[i][j] += this->structure[i][r] * otherMatrix.structure[r][j];
            }
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

void Matrix::validate(unsigned int row, unsigned int column){
    if (row < 0 || row >= this->m) {
        throw std::out_of_range("Row value exceeds matrix dimensions");
    }
    if (column < 0 || column >= this->n) {
        throw std::out_of_range("Column value exceeds matrix dimensions");
    }
}