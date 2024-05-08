#pragma once
#include <vector>
#include <ostream>
#include <functional>

#include "Math.hpp"

namespace Math
{
    template <typename T>
    class Matrix
    {
    public:
        using MatrixVector = std::vector<std::vector<T>>;
        using LambdaDoubleUpdater = std::function<T(const T&, const T&)>;

        Matrix(size_t width = 1, size_t height = 1, std::initializer_list<T> vectors = {});
        
        Matrix(const Matrix<T>& other);
        
        Matrix(const MatrixVector& vector);
        
        Matrix& operator=(const Matrix<T>& other);

        virtual ~Matrix() = default;

        double Determinant(void) const;

        size_t Height(void) const noexcept;
        
        size_t Width(void) const noexcept;

        const MatrixVector& Vector(void) const noexcept;
        
        MatrixVector& Vector(void) noexcept;

        Matrix<T>& Resize(size_t width, size_t height);

        Matrix<T>& Fill(const T& vector) noexcept;

        Matrix<T>& Fill(std::function<T(const T&)> lambda);

        static Matrix<T> Identity(size_t order);
        
        constexpr bool IsSquare(void) const;

        std::vector<T>& operator[](size_t index);
        
        const std::vector<T>& operator[](size_t index) const;

        std::vector<T>& At(size_t index);
        
        const std::vector<T>& At(size_t index) const;
        
        Matrix<T> operator+(const Matrix<T>& other) const;

        Matrix<T> operator+(const T& vector) const;

        Matrix<T> operator-(void) const;

        Matrix<T> operator-(const Matrix<T>& other) const;

        Matrix<T> operator-(const T& vector) const;

        Matrix<T> operator*(const Matrix<T>& other) const;

        Matrix<T> operator*(const T& vector) const;

        Matrix<T> operator/(const T& vector) const;
        
        bool operator==(const Matrix<T>& other) const;
        
        operator bool(void) const;

        friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix)
        {
            for (const std::vector<T>& row : matrix._matrixVector)
            {
                for (const T& elem : row)
                    out << elem << ' ';

                out << '\n';
            }

            return out;
        }

    private:
        Matrix<T> FullDoubleIteration(const LambdaDoubleUpdater& lambda, const Matrix<T>& other) const;

    private:
        size_t _width;
        size_t _height;
        MatrixVector _matrixVector;
    };
}
