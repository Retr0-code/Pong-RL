#include "FunctionContext.hpp"

using namespace Math;

template<typename T>
FunctionContext<T>::FunctionContext(const std::vector<LayerPair>& layers)
{
    for (const auto& layer : layers)
        AddLayer(layer);
}

template <typename T>
void FunctionContext<T>::AddLayer(const LayerPair& layer)
{
    size_t size{layer.first};
    const ActivationFunction& activation{layer.second};

    _layers.push_back(std::vector<T>(size));
    _weights.push_back(Matrix<T>(size, (_layers.end() - 1)->size()));
    _layersActivation.push_back(activation);
}

template <typename T>
Matrix<T> FunctionContext<T>::Forward(const Matrix<T> &input) const
{
    return Matrix<T>();
}

template <typename T>
const std::vector<Matrix<T>> &FunctionContext<T>::GetWeights(void) const
{
    return _weights;
}

template <typename T>
const std::vector<std::vector<T>> &FunctionContext<T>::GetLayers(void) const
{
    return _layers;
}

template <typename T>
const std::vector<Matrix<T>> &FunctionContext<T>::SetRandomWeights(void)
{
    return _weights;
}

template class FunctionContext<int>;
template class FunctionContext<float>;
template class FunctionContext<double>;
