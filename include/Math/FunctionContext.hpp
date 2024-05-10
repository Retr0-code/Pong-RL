#pragma once
#include <random>

#include "Math.hpp"
#include "Matrix.hpp"

namespace Math
{
    template <typename T>
    class FunctionContext
    {
    public:
        using ActivationFunction = Matrix<T> (*)(const Matrix<T>&);
        using LayerPair = std::pair<size_t, ActivationFunction>;

        FunctionContext(const std::vector<LayerPair>& layers);

        virtual ~FunctionContext() = default;

        void AddLayer(const LayerPair& layer);

        const std::vector<T>& Forward(const std::vector<T>& input);

        const std::vector<Matrix<T>>& Weights(void) const;
        
        const std::vector<std::vector<T>>& Layers(void) const;
        
        template <typename RNG>
        const std::vector<Matrix<T>>& SetRandomWeights(T lower, T upper)
        {
            RNG engine;
            std::uniform_real_distribution<T> distribution(lower, upper);

            for (auto& layer : _weights)
                for (auto& row : layer.Vector())
                    for (auto& elem : row)
                        elem = distribution(engine);
            
            return _weights;
        }

    protected:
        std::vector<std::vector<T>> _layers;
        std::vector<Matrix<T>> _weights;
        std::vector<ActivationFunction> _layersActivation;

    private:
        static Matrix<T> Propogate(const std::vector<T>& input, const Matrix<T>& weights);
    };
}