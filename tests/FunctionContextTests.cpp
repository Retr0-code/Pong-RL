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
    BOOST_TEST(sequence.GetLayers());
}