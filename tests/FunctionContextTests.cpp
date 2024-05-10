#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FunctionContextTest 

#include <boost/test/unit_test.hpp>

#include "Math/Math.hpp"
#include "Math/FunctionContext.hpp"

using Math::Matrix;
using Math::FunctionContext;

BOOST_AUTO_TEST_CASE(test_FunctionContext)
{
    FunctionContext<float> sequence({
        {4, &Math::Linear},
        {32, &Math::ReLU},
        {1, &Math::Sigmoid}
    });
    BOOST_TEST(sequence.GetLayers()[0].size() == 4);
    BOOST_TEST(sequence.GetLayers()[1].size() == 32);
    BOOST_TEST(sequence.GetLayers()[2].size() == 1);

    sequence.SetRandomWeights<std::default_random_engine>(0.f, 1.f);
    for (auto& matrix : sequence.GetWeights())
        std::cout << matrix << '\n';

    
}