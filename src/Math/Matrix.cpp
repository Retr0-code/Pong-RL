#include <stdexcept>
#include <algorithm>
#include <initializer_list>

#include "Matrix.hpp"

using namespace Math;

template <typename T>
using MatrixVector = std::vector<std::vector<T>>;

template <typename T>
Matrix<T>::Matrix(size_t width, size_t height, std::initializer_list<T> vectors)
    : _width(width), _height(height), _matrixVector(height)
{   
    for (auto& row : _matrixVector)
        row.resize(_width);

    size_t row{0}, column{0};
    for (auto element : vectors)
    {
        if (row >= _height)
                break;

        _matrixVector[row][column] = element;

        ++column;
        if (column == _width)
        {
            ++row;
            column = 0;
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : _height(other._height), _width(other._width), _matrixVector(other._matrixVector) {  }

template <typename T>
Matrix<T>::Matrix(const MatrixVector &vector)
    : _height(vector.size()), _width(vector[0].size()), _matrixVector(vector) {  }

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    _height = other._height;
    _width = other._width;
    _matrixVector = other._matrixVector;
    return *this;
}

template <typename T>
size_t Matrix<T>::Height(void) const noexcept
{
    return _height;
}

template <typename T>
size_t Matrix<T>::Width(void) const noexcept
{
    return _width;
}

template <typename T>
const MatrixVector<T> &Matrix<T>::Vector(void) const noexcept
{
    return _matrixVector;
}

template <typename T>
void Matrix<T>::Resize(size_t width, size_t height)
{
    if (height != _height)
        _matrixVector.resize(height);
        
    if (width != _width)
        for (auto& row : _matrixVector)
            row.resize(width);

    _height = height;
    _width = width;
}

template <typename T>
void Math::Matrix<T>::Fill(const T &vector) noexcept
{
    for (std::vector<T> &row : _matrixVector)
        for (T& elem : row)
            elem = vector;
}

template <typename T>
void Matrix<T>::Fill(std::function<T(const T&)> lambda)
{
    for (std::vector<T> &row : _matrixVector)
        for (T& elem : row)
            elem = lambda(elem);
}

template <typename T>
Matrix<T> Matrix<T>::Identity(size_t order)
{
    Matrix<T> identity(order, order);
    for (; order != 0; --order)
        identity[order - 1][order - 1] = 1;

    return identity;
}

template <typename T>
constexpr bool Matrix<T>::IsSquare(void) const
{
    return _height == _width;
}

template <typename T>
std::vector<T> &Matrix<T>::operator[](size_t index)
{
    if (index >= _height)
        throw std::out_of_range{"Error in [std::vector<T> &Matrix<T>::operator[](size_t index)]\n\tindex is out of range."};

    return _matrixVector[index];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](size_t index) const
{
    if (index >= _height)
        throw std::out_of_range{"Error in [const std::vector<T> &Matrix<T>::operator[](size_t index) const]\n\tindex is out of range."};

    return _matrixVector[index];
}

template <typename T>
std::vector<T> &Matrix<T>::At(size_t index)
{
    if (index >= _height)
        throw std::out_of_range{"Error in [std::vector<T> &Matrix<T>::At(size_t index)]\n\tindex is out of range."};

    return _matrixVector.at(index);
}

template <typename T>
const std::vector<T> &Matrix<T>::At(size_t index) const
{
    if (index >= _height)
        throw std::out_of_range{"Error in [const std::vector<T> &Matrix<T>::At(size_t index) const]\n\tindex is out of range."};

    return _matrixVector.at(index);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{
    if (other._height != _height || other._width != _width)
        throw std::invalid_argument{"Error in [Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const]\n\tmatrixes' sizes do not match.\n"};

    LambdaUpdater lambdaSum([&](const T& elemIterFirst, const T& elemIterSecond) -> T
    {
            return elemIterFirst + elemIterSecond;
    });

    return FullDoubleIteration(lambdaSum, other);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const T &vector) const
{
    if (!IsSquare())
        throw std::invalid_argument{"Error in [Matrix<T> Matrix<T>::operator+(const T &vector) const] given matrix is not square."};
    
    return *this + (Identity(_height) * vector);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(void) const
{
    Matrix<T> inversed(*this);
    inversed.Fill([](const T& elem)
    {
        return -elem;
    });

    return inversed;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) const
{
    return *this + (-other);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const T &vector) const
{
    return *this - (Identity(_height) * vector);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const
{
    if (_width != other._height)
        throw std::invalid_argument{"Error in [Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const]\n\twidth and height are different."};

    Matrix<T> multiplied(other._width, _height);
    for (size_t row{0}; row < multiplied._height; ++row)
        for (size_t column{0}; column < multiplied._width; ++column)
            for (size_t elemIndex{0}; elemIndex < _width; ++elemIndex)
                multiplied[row][column] += _matrixVector[row][elemIndex] * other._matrixVector[elemIndex][column];

    return multiplied;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &vector) const
{
    Matrix<T> other(_width, _height);
    other.Fill(vector);

    LambdaUpdater lambdaMultiply([&](const T& elemIterFirst, const T& elemIterSecond) -> T
    {
            return elemIterFirst * elemIterSecond;
    });

    return FullDoubleIteration(lambdaMultiply, other);
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T &vector) const
{
    Matrix<T> other(_width, _height);
    other.Fill(vector);

    LambdaUpdater lambdaDivide([&](const T& elemIterFirst, const T& elemIterSecond) -> T
    {
            return elemIterFirst / elemIterSecond;
    });

    return FullDoubleIteration(lambdaDivide, other);
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &other) const
{
    for (size_t row{0}; row < _height; ++row)
        for (size_t column{0}; column < _width; ++column)
            if (_matrixVector[row][column] != other._matrixVector[row][column])
                return false;

    return true;
}

template <typename T>
Math::Matrix<T>::operator bool(void) const
{
    Matrix<T> nullMatrix(_width, _height);
    return *this == nullMatrix;
}

template <typename T>
Matrix<T> Matrix<T>::FullDoubleIteration(const LambdaUpdater& lambda, const Matrix<T>& other) const
{
    Matrix<T> result(_width, _height);
    std::transform(_matrixVector.begin(), _matrixVector.end(), other._matrixVector.begin(), result._matrixVector.begin(), 
    [&](const std::vector<T>& rowIterFirst, const std::vector<T>& rowIterSecond)
    {
        std::vector<T> subResult(_width);
        
        std::transform(
            rowIterFirst.begin(), rowIterFirst.end(),
            rowIterSecond.begin(), subResult.begin(),
            lambda
            );

        return subResult;
    });
    
    return result;
}

template class Matrix<int>;
