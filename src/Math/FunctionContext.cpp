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
const std::vector<T>& FunctionContext<T>::Forward(const std::vector<T> &input)
{
    if (input.size() != _layers.size())
        throw std::invalid_argument{"Error in [Matrix<T> FunctionContext<T>::Forward(const Matrix<T> &input) const]\n\tinput vector does not match inputs amount."};
    
    _layers[0] = input;

    std::transform(
        _layers.begin(), _layers.end() - 1,
        _weights.begin(), _layers.begin() + 1,
        &FunctionContext::Propogate
    // [&](const std::vector<T>& input, const Matrix<T>& weights)
    // {
    //     return Propogate(input, weights);
    // }
    );

    return *(_layers.end() - 1);
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
std::vector<T> Math::FunctionContext<T>::Propogate(const std::vector<T> &input, const Matrix<T> &weights)
{
    Matrix<T> inputVector({input});
    return (inputVector * weights)[0];
}

template class FunctionContext<int>;
template class FunctionContext<float>;
template class FunctionContext<double>;
