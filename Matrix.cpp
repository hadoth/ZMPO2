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

/**
 * Konstruktor kopiujący
 *
 * Konstruktor ten tworzy niezależną kopię oryginalnego obiektu. Jest wykorzystywany wszędzie tam gdzie
 * niezbędne jest utworzenie identycznego, nieodróżnialnego obiektu, a nie jest dla użytkownika istotne, czy
 * istnieje więcej niż jedna instancja danego obiektu. Wszelkie zdefiniowane dla danego obiektu funkcje i operatory
 * porównujące (equals, comparator, "==") powinny traktować oryginał i kopię obiektu jako tożsame. Ponadto, żadna ze zmian
 * dokonanych na oryginale nie powinna wpływać na kopię i odwrotnie, żadna ze zmian dokonanych na kopii nie powinna
 * wpływać na oryginał.
 * Jeżeli nie został przeciążony operator "=" i został zdefiniowany konstruktor kopiujący, to wywołanie "Matrix a = b"
 * będzie skutkować wywołaniem konstruktora kopiującego tworzącego obiekt b będący kopią obiektu a.
 *
 * @param matrixToCopy
 */
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

/**
 * Konstruktor przenoszący
 *
 * Konstruktor ten operuje na tzw. rvalue. Efektem działania konstruktora przenoszącego jest nowy obiekt będący
 * nieodróżnialny od oryginału przekazanego w konstruktorze. Wspomniany oryginał powinien natomiast przejść w stan neutralny,
 * to znaczy taki, który nie pozwala na dostęp do żadnej z uprzednio przechowywanych danych oraz nie wpływa na dalszą
 * pracę programu. Konstruktor przenoszący wykorzystywany jest głównie poprzez standardowe biblioteki c++, np. funkcja
 * move i struktura vector. Konstruktor przenoszący powinien być wykorzystywany wszędzie tam, gdzie niezbędne jest
 * przypisanie obiektu do innej zmiennej, a niewskazane jest  tworzenie nowych instancji obiektów (np. utworzenie obiektu
 * z wykorzystaniem domyślnego konstruktora jest czasochłonne), lub instancjonowanie/destrukcja obiektów wiąże się
 * z dodatkowymi operacjami wpływającymi na pracę innych części programu (np. tworzenie i zwalnianie "locków" na zasoby).
 *
 * @param matrixToMove
 */

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
    Matrix result(this->m, this->n);

    for (int i = 0; i < result.m; i++) {
        for (int j = 0; j < result.n; j++) {
            result.structure[i][j] = this->structure[i][j] * scalar;
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