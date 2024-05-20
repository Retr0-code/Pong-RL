#pragma once
#include <cmath>

#include "Matrix.hpp"
#include "FunctionContext.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#ifndef M_E
#define M_E 2.718281828f
#endif

/**
 * @brief Namespace for all math functions and classes
 */
namespace Math
{
    template<typename T>
    class Matrix;

    template <typename T>
    class FunctionContext;

    /**
     * @brief Rectified linear unit function for single vector
     * 
     * @tparam T type of vector
     * @param vector input object
     * @return T vector > 0 ? vector : 0
     */
    template <typename T>
    T ReLU(const T &vector) noexcept
    {
        return vector > 0 ? vector : 0;
    }

    /**
     * @brief Sigmoid function for single vector
     * 
     * @tparam T type of vector
     * @param vector input object
     * @return T 1 / (1 + std::pow(M_E, -vector))
     */
    template <typename T>
    T Sigmoid(const T& vector) noexcept
    {
        return 1 / (1 + std::pow(M_E, -vector));
    }

    /**
     * @brief Linear function for single vector
     * 
     * @tparam T type of vector
     * @param vector input object
     * @return T vector
     */
    template <typename T>
    T Linear(const T& vector) noexcept
    {
        return vector;
    }

    /**
     * @brief Rectified linear unit function for tensor/matrix
     * 
     * @tparam T type of vector
     * @param matrix input object
     * @return Matrix<T> [for (every vector) : `Math::ReLU(const T& vector)`]
     */
    template <typename T>
    Matrix<T> ReLU(const Matrix<T>& matrix)
    {
        const std::function<T(const T&)>& lambdaRelu([&](const T& inputValue)
        {
            return Math::ReLU(inputValue);
        });
        
        return UpdateIterateThrouhMatrix(lambdaRelu, matrix);
    }

    /**
     * @brief Sigmoid function for tensor/matrix
     * 
     * @tparam T type of vector
     * @param matrix input object
     * @return Matrix<T> [for (every vector) : `Math::Sigmoid(const T& vector)`]
     */
    template <typename T>
    Matrix<T> Sigmoid(const Matrix<T>& matrix)
    {
        const std::function<T(const T&)>& lambdaSigmoid([&](const T& inputValue)
        {
            return Math::Sigmoid(inputValue);
        });

        return UpdateIterateThrouhMatrix(lambdaSigmoid, matrix);
    }

    /**
     * @brief Sigmoid function for tensor/matrix
     * 
     * @tparam T type of vector
     * @param matrix input object
     * @return Matrix<T> matrix
     */
    template <typename T>
    Matrix<T> Linear(const Matrix<T>& matrix)
    {
        return matrix;
    }
    
    /**
     * @brief Backend function for matrix activation functions
     * 
     * @tparam T 
     * @param lambda activation function for single vector
     * @param input input matrix 
     * @return Matrix<T> after activation
     */
    template <typename T>
    static Matrix<T> UpdateIterateThrouhMatrix(const std::function<T(const T&)>& lambda, const Matrix<T>& input)
    {
        Matrix<T> outputMatrix(input.Width(), input.Height());
        std::transform(input.Vector().begin(), input.Vector().end(), outputMatrix.Vector().begin(),
        [&](const std::vector<T>& inputVector)
        {
            std::vector<T> outputVector(inputVector.size());
            std::transform(inputVector.begin(), inputVector.end(), outputVector.begin(), lambda);
            return outputVector;
        });
        return outputMatrix;
    }
}
