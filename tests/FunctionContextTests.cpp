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

    BOOST_TEST(sequence.Layers()[0].size() == 4);
    BOOST_TEST(sequence.Layers()[1].size() == 32);
    BOOST_TEST(sequence.Layers()[2].size() == 1);
    BOOST_TEST(sequence.Weights()[0].Width() == 32);
    BOOST_TEST(sequence.Weights()[0].Height() == 4);
    BOOST_TEST(sequence.Weights()[1].Width() == 1);
    BOOST_TEST(sequence.Weights()[1].Height() == 32);

    sequence.SetRandomWeights<std::default_random_engine>(0.f, 1.f);
    for (auto& matrix : sequence.Weights())
        std::cout << matrix << '\n';

    sequence.Forward({1, 2, 3, 4});
    for (auto& vector : sequence.Layers())
    {
        for (auto& elem : vector)
            std::cout << elem << ' ';
        std::cout << '\n';
    }
}