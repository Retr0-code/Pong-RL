#pragma once
#include <cmath>

#include "Matrix.hpp"

namespace Math
{
    template<typename T>
    class Matrix;

    template <typename T>
    T ReLU(const T &vector) noexcept
    {
        return vector > 0 ? vector : 0;
    }

    template <typename T>
    T Sigmoid(const T& vector) noexcept
    {
        return 1 / (1 + std::pow(M_E, -vector));
    }

    template <typename T>
    T Linear(const T& vector) noexcept
    {
        return vector;
    }

    template <typename T>
    Matrix<T> ReLU(const Matrix<T>& matrix)
    {
        const std::function<T(const T&)>& lambdaRelu([&](const T& inputValue)
        {
            return Math::ReLU(inputValue);
        });
        
        return UpdateIterateThrouhMatrix(lambdaRelu, matrix);
    }

    template <typename T>
    Matrix<T> Sigmoid(const Matrix<T>& matrix)
    {
        const std::function<T(const T&)>& lambdaSigmoid([&](const T& inputValue)
        {
            return Math::Sigmoid(inputValue);
        });

        return UpdateIterateThrouhMatrix(lambdaSigmoid, matrix);
    }

    template <typename T>
    Matrix<T> Linear(const Matrix<T>& matrix)
    {
        return matrix;
    }
    
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
