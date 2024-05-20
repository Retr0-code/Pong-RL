#pragma once
#include <vector>
#include <ostream>
#include <functional>

#include "Math.hpp"

namespace Math
{
    /**
     * @brief Matrix/Tensor class
     * 
     * @tparam T calculations type
     */
    template <typename T>
    class Matrix
    {
    public:
        /**
         * @brief alias for std::vector<std::vector<T>>
         */
        using MatrixVector = std::vector<std::vector<T>>;
        /**
         * @brief alias for std::function<T(const T&, const T&)>
         */
        using LambdaDoubleUpdater = std::function<T(const T&, const T&)>;

        /**
         * @brief Construct a new Matrix object
         * 
         * @param width width of a matrix (default is 1)
         * @param height height of a matrix (default is 1)
         * @param vectors values matrix ordered by rows
         */
        Matrix(size_t width = 1, size_t height = 1, std::initializer_list<T> vectors = {});
        
        /**
         * @brief Construct a new Matrix object by copieng it
         * 
         * @param other matrix to be copied
         */
        Matrix(const Matrix<T>& other);
        
        /**
         * @brief Construct a new Matrix object by initializing it from vectors
         * 
         * @param vector input std::vector matrix representation
         */
        Matrix(const MatrixVector& vector);
        
        /**
         * @brief Copy/Assign operator overload
         * 
         * @param other matrix to be copied
         * @return Matrix& this object
         */
        Matrix& operator=(const Matrix<T>& other);

        virtual ~Matrix() = default;

        /**
         * @brief Matrix determinant
         * 
         * @return double value of the determinant
         */
        double Determinant(void) const;

        /**
         * @brief Getter for height value
         * 
         * @return size_t height value
         */
        size_t Height(void) const noexcept;
        
        /**
         * @brief Getter for width value
         * 
         * @return size_t width value
         */
        size_t Width(void) const noexcept;

        /**
         * @brief Constant getter of matrix backend vector
         * 
         * @return const MatrixVector& backend vector<vector<T>>
         */
        const MatrixVector& Vector(void) const noexcept;
        
        /**
         * @brief Getter of matrix backend vector
         * 
         * @return MatrixVector& backend vector<vector<T>>
         */
        MatrixVector& Vector(void) noexcept;

        /**
         * @brief Resizes the matrix
         * 
         * @param width new width value
         * @param height new height value
         * @return Matrix<T>& this object
         */
        Matrix<T>& Resize(size_t width, size_t height);

        /**
         * @brief Fill matrix with one value
         * 
         * @param vector value
         * @return Matrix<T>& this object
         */
        Matrix<T>& Fill(const T& vector) noexcept;

        /**
         * @brief Fill matrix with value of lambda dependent on current matrix values
         * 
         * @param lambda function for filling matrix
         * @return Matrix<T>& this object
         */
        Matrix<T>& Fill(std::function<T(const T&)> lambda);

        /**
         * @brief Identity matrix of `order`
         * 
         * @param order size of square matrix
         * @return Matrix<T> 
         */
        static Matrix<T> Identity(size_t order);
        
        /**
         * @brief Check if matrix is square
         * 
         * @return true is square
         * @return false not square
         */
        constexpr bool IsSquare(void) const;

        /**
         * @brief Access operator overload
         * 
         * @param index index of row
         * @return std::vector<T>& matrix row
         */
        std::vector<T>& operator[](size_t index);
        
        /**
         * @brief Const access operator overload
         * 
         * @param index index of row
         * @return const std::vector<T>& matrix row
         */
        const std::vector<T>& operator[](size_t index) const;

        /**
         * @brief Access function
         * 
         * @param index index of row
         * @return std::vector<T>& matrix row
         */
        std::vector<T>& At(size_t index);
        
        /**
         * @brief Const access function
         * 
         * @param index index of row
         * @return const std::vector<T>& matrix row
         */
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
