#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <windows.h>

using namespace std;

class IntMatrix {
private:
    vector<vector<int>> data;

public:
    IntMatrix() {}

    IntMatrix(initializer_list<vector<int>> list) : data(list) {}

    vector<int>& operator[](int index) {
        if (index < 0 || index >= data.size()) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    int maxElement() const {
        if (data.empty() || data[0].empty()) {
            throw length_error("Matrix is empty");
        }

        int maxElem = data[0][0];
        for (const auto& row : data) {
            auto rowMax = max_element(row.begin(), row.end());
            maxElem = max(maxElem, *rowMax);
        }
        return maxElem;
    }

    int minElement() const {
        if (data.empty() || data[0].empty()) {
            throw length_error("Matrix is empty");
        }

        int minElem = data[0][0];
        for (const auto& row : data) {
            auto rowMin = min_element(row.begin(), row.end());
            minElem = min(minElem, *rowMin);
        }
        return minElem;
    }

    IntMatrix operator*(const IntMatrix& other) const {
        if (data.empty() || other.data.empty() || this->data[0].size() != other.data.size()) {
            throw length_error("Matrix dimensions do not match for multiplication");
        }

        IntMatrix result;
        result.data.resize(this->data.size(), vector<int>(other.data[0].size(), 0));

        for (size_t i = 0; i < this->data.size(); ++i) {
            for (size_t j = 0; j < other.data[0].size(); ++j) {
                for (size_t k = 0; k < other.data.size(); ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    void fillByUserInput() {
        int rows, cols;
        cout << "Введіть кількість рядків матриці: ";
        cin >> rows;
        cout << "Введіть кількість стовпців матриці: ";
        cin >> cols;

        data.resize(rows, vector<int>(cols));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "Елемент [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
        }
    }

    void print() const {
        for (const auto& row : data) {
            for (int elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    IntMatrix m1, m2;

    cout << "Введіть елементи першої матриці:\n";
    m1.fillByUserInput();
    cout << "Введіть елементи другої матриці:\n";
    m2.fillByUserInput();

    try {
        cout << "Максимальний елемент матриці m1: " << m1.maxElement() << endl;
        cout << "Мінімальний елемент матриці m1: " << m1.minElement() << endl;

        cout << "Максимальний елемент матриці m2: " << m2.maxElement() << endl;
        cout << "Мінімальний елемент матриці m2: " << m2.minElement() << endl;

        cout << "Множення матриць m1 та m2:" << endl;
        IntMatrix result = m1 * m2;
        result.print();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
