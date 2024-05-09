#pragma once
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

        Matrix<T> Forward(const Matrix<T>& input) const;

        const std::vector<Matrix<T>>& GetWeights(void) const;
        
        const std::vector<std::vector<T>>& GetLayers(void) const;
        
        const std::vector<Matrix<T>>& SetRandomWeights(void);

    protected:
        std::vector<std::vector<T>> _layers;
        std::vector<Matrix<T>> _weights;
        std::vector<ActivationFunction> _layersActivation;

    private:


    };
}