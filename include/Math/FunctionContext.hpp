#pragma once
#include <random>

#include "Math.hpp"
#include "Matrix.hpp"

namespace Math
{
    /**
     * @brief FunctionContext class is an analog of tensorflow sequential
     * 
     * @tparam T calculations type
     */
    template <typename T>
    class FunctionContext
    {
    public:
        /**
         * @brief alias for Matrix<T> (*)(const Matrix<T>&)
         */
        using ActivationFunction = Matrix<T> (*)(const Matrix<T>&);
        /**
         * @brief alias for std::pair<size_t, ActivationFunction>
         */
        using LayerPair = std::pair<size_t, ActivationFunction>;

        /**
         * @brief Construct a new FunctionContext object
         * 
         * @param layers vector of pairs of layer's size and activation function
         */
        FunctionContext(const std::vector<LayerPair>& layers);

        virtual ~FunctionContext() = default;

        /**
         * @brief Add layer to end of sequence
         * 
         * @param layer pair of layer's size and activation function
         */
        void AddLayer(const LayerPair& layer);

        /**
         * @brief Forward propagation
         * 
         * @param input vector of input values
         * @return const std::vector<T>& output values of last layer
         */
        const std::vector<T>& Forward(const std::vector<T>& input);

        /**
         * @brief Getter for weights object
         * 
         * @return const std::vector<Matrix<T>>& weights
         */
        const std::vector<Matrix<T>>& Weights(void) const;
        
        /**
         * @brief Getter for layers object
         * 
         * @return const std::vector<std::vector<T>>&  layers
         */
        const std::vector<std::vector<T>>& Layers(void) const;
        
        /**
         * @brief Initialize weights with random numbers
         * 
         * @tparam RNG random number engine
         * @param lower lower bound
         * @param upper upper bound
         * @return const std::vector<Matrix<T>>& initialized weights
         */
        template <typename RNG>
        const std::vector<Matrix<T>>& SetRandomWeights(T lower, T upper)
        {
            std::random_device seed;
            RNG engine(seed());
            std::uniform_real_distribution<T> distribution(lower, upper);

            for (auto& layer : _weights)
                for (auto& row : layer.Vector())
                    for (auto& elem : row)
                        elem = distribution(engine);
            
            return _weights;
        }

    protected:
        std::vector<std::vector<T>> _layers; // Vector of all NN layers
        std::vector<Matrix<T>> _weights; // Vector of NN weights
        std::vector<ActivationFunction> _layersActivation; // Vector of layers activation functions

    private:
        static Matrix<T> Propogate(const std::vector<T>& input, const Matrix<T>& weights);
    };
}