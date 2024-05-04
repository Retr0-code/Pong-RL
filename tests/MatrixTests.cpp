#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MatrixTest 

#include <boost/test/unit_test.hpp>

#include "../src/Math/Matrix.hpp"

using Math::Matrix;

BOOST_AUTO_TEST_CASE(test_MatrixConstructor)
{
    BOOST_TEST(Matrix<int>(2, 2) == Matrix<int>(2, 2, {0, 0, 0, 0}));
    BOOST_TEST(Matrix<int>(2, 2, {1, 2, 3, 4, 5, 6}) == Matrix<int>({{1, 2}, {3, 4}})); 
    Matrix<int> A(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    Matrix<int> B(A);
    BOOST_TEST(B == A);
    B = Matrix<int>::Identity(3);
    BOOST_TEST(B == Matrix<int>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}));
}

BOOST_AUTO_TEST_CASE(test_MatrixMiscFunctions)
{
    // Resize
    // operator[]
    // At
    // Fill
    // IsSquare
    // Determinant
}

BOOST_AUTO_TEST_CASE(test_MatrixArithmetic)
{
    Matrix<int> A(2, 2, {1, 0, 0, 1});
    Matrix<int> B(2, 3, {1, 2, 3, 4, 5, 6});
    BOOST_CHECK_THROW(A * B, std::invalid_argument);
    BOOST_TEST(B * A == B);
    BOOST_CHECK_THROW(A + B, std::invalid_argument);
    B.Resize(2, 2);
    BOOST_TEST(B + A == Matrix<int>(2, 2, {2, 2, 3, 5}));
}
