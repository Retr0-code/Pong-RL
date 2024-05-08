#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MatrixTest 

#include <boost/test/unit_test.hpp>

#include "Math/Math.hpp"

using Math::Matrix;

BOOST_AUTO_TEST_CASE(test_ValueActivationFunctions)
{
    BOOST_TEST(Math::ReLU(-10) == 0);
    BOOST_TEST(Math::ReLU(10) == 10);
    BOOST_TEST(Math::ReLU(0) == 0);
    BOOST_TEST(Math::Sigmoid(double(-10.0)) - 0.00004539 <= 0.00001);
    BOOST_TEST(Math::Sigmoid(double(10.0)) - 0.999 <= 0.001);
}


BOOST_AUTO_TEST_CASE(test_MatrixActivationFunctions)
{
    Matrix<double> A(2, 4, {0.001, -0.02, -1.0, 1.0, 2.0, 3.0, -3.0, 10.0});
    Matrix<double> B(1, 2, {-10.0, 10.0});
    BOOST_TEST(Math::ReLU(A) == Matrix<double>({{0.001, 0.0}, {0.0, 1.0}, {2.0, 3.0}, {0.0, 10.0}}));
    Matrix<double> B_s(Math::Sigmoid(B));
    BOOST_TEST(B_s[0][0] - 0.999 <= 0.001);
    BOOST_TEST(B_s[0][1] - 0.999 <= 0.001);
}