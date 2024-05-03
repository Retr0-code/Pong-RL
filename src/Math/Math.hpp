#pragma once
#include <cmath>

#include "Matrix.hpp"

namespace Math
{
    template <typename T>
    T ReLU(const T& vector);

    template <typename T>
    T Sigmoid(const T& vector);
}
