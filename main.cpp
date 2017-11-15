#include <iostream>
#include "Matrix.h"

int main() {
    Matrix m1(2, 3);
    Matrix m2(2, 3);

    m1.setValue(0, 0, 1);
    m1.setValue(0, 1, 2);
    m1.setValue(0, 2, 3);
    m1.setValue(1, 0, 5);
    m1.setValue(1, 1, 7);
    m1.setValue(1, 2, 11);

    m2.setValue(0, 0, 13);
    m2.setValue(0, 1, 17);
    m2.setValue(0, 2, 23);
    m2.setValue(1, 0, 29);
    m2.setValue(1, 1, 31);
    m2.setValue(1, 2, 37);

    Matrix m3(m1.add(m2));

    m1.print();
    std::cout << std::endl;
    m2.print();
    std::cout << std::endl;
    m3.print();
    std::cout << std::endl;
    Matrix m4 = std::move(m1);
    m1.print();
    std::cout << std::endl;
    m4.print();
    std::cout << std::endl;

    m4.setValue(0,1,9000);
    std::cout << m4.getValue(0,1) << std::endl;
    std::cout << "m4: " << m4.getColumns() << " x " << m4.getRows() << std::endl;

    std::cout << std::endl;
    m4.print();
    std::cout << std::endl;
    Matrix m5 = m4.multiply(3);
    m5.print();
    std::cout << std::endl;
    m4.print();
    std::cout << std::endl;

    return 0;
}