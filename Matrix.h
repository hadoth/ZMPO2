#ifndef ZMPO2_MATRIX_H
#define ZMPO2_MATRIX_H


class Matrix {
private:
    unsigned int m;
    unsigned int n;
    int **structure;
    void makeEmpty();
    void validate(unsigned int row, unsigned int column);
public:
    Matrix();
    Matrix(unsigned int rows, unsigned int columns);
    Matrix(Matrix &matrixToCopy);
    Matrix(Matrix &&matrixToMove);
    ~Matrix();
    Matrix add(Matrix matrixToAdd);
    Matrix multiply(int scalar);
    Matrix multiply(Matrix matrix);
    void setValue(unsigned int row, unsigned int column, int value);
    int getValue(unsigned int row, unsigned int column);
    inline unsigned int getRows() { return m;}
    inline unsigned int getColumns() { return n;}
    void print();
};


#endif //ZMPO2_MATRIX_H
