#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
// * оператор ввода для класса Matrix из потока istream
// * оператор вывода класса Matrix в поток ostream
// * оператор проверки на равенство двух объектов класса Matrix
// * оператор сложения двух объектов класса Matrix
class Matrix {
public:
    Matrix():_rows(0),_cols(0){};
    Matrix(int num_rows, int num_cols):_rows(num_rows),_cols(num_cols){
        Reset(num_rows, num_cols);
    };
    void Reset(int num_rows, int num_cols)  {
        if(num_rows < 0 || num_cols < 0) {
            throw std::out_of_range("negative index");
        }

        _rows = num_rows;
        _cols = num_cols;
        data.resize(_rows * _cols);
        fill(begin(data), end(data), 0);
    }
    int At(int row, int col) const {
        if(row >= _rows || col >= _cols) {
            throw out_of_range("index");
        }
        return data[row * _cols + col];
    }
    int& At(int row, int col) {
        if(row >= _rows || col >= _cols) {
            throw out_of_range("index");
        }
        return data[row * _cols + col];
    }

    unsigned GetNumRows() const {
        return _rows;
    }

    unsigned GetNumColumns() const {
        return _cols;
    }
private:
    unsigned _rows;
    unsigned _cols;
    vector<int> data;
};

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    unsigned lsize = lhs.GetNumColumns() * lhs.GetNumRows();
    unsigned rsize = rhs.GetNumColumns() * rhs.GetNumRows();
    if(lsize == 0 && lsize == rsize) {
        return Matrix();
    }

    if (lhs.GetNumColumns() != rhs.GetNumColumns() || lhs.GetNumRows() != rhs.GetNumRows()) {
        throw invalid_argument("different dimensions " +
                               to_string(lhs.GetNumRows()) + "x" + to_string(lhs.GetNumColumns()) + " " +
                               to_string(rhs.GetNumRows()) + "x" + to_string(rhs.GetNumColumns())
        );
    }

    Matrix sum(lhs.GetNumRows(), lhs.GetNumColumns());
    for(unsigned i = 0; i < lhs.GetNumRows(); ++i) {
        for(unsigned j = 0; j < lhs.GetNumColumns(); ++j) {
            sum.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return sum;
}

bool operator==(const Matrix& lhs, const Matrix& rhs)
{
    unsigned lsize = lhs.GetNumColumns() * lhs.GetNumRows();
    unsigned rsize = rhs.GetNumColumns() * rhs.GetNumRows();
    if(lsize == 0 && lsize == rsize) {
        return true;
    }
    if(lhs.GetNumColumns() != rhs.GetNumColumns() || lhs.GetNumRows() != rhs.GetNumRows()) {
        return false;
    }
    for(unsigned i = 0; i < lhs.GetNumRows(); ++i) {
        for(unsigned j = 0; j < lhs.GetNumColumns(); ++j) {
            if(lhs.At(i, j) != rhs.At(i, j)) {
                return false;
            }
        }
    }
    return true;
}

istream& operator>>(istream& stream, Matrix& matrix)
{
    int rows, cols;
    stream >> rows >> cols;
    matrix.Reset(rows, cols);
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            stream >> matrix.At(i, j);
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
    stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for(int i = 0; i < matrix.GetNumRows(); ++i) {
        for(int j = 0; j < matrix.GetNumColumns(); ++j) {
            stream << matrix.At(i, j);
            if(j != matrix.GetNumColumns() - 1) {
                stream << " ";
            }
        }
        stream << endl;
    }
    return stream;
}
int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}