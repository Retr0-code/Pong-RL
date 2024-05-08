#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MatrixTest 

#include <boost/test/unit_test.hpp>

#include "Math/Matrix.hpp"

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
    Matrix<int> A(1, 1, {1});
    BOOST_TEST(A.Resize(2, 3) == Matrix<int>({{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}));
    // operator[]
    BOOST_CHECK_THROW(A[3], std::out_of_range);
    std::vector<int> row = {1, 2, 3};
    BOOST_TEST((A[2] = row) == row);
    // At
    BOOST_CHECK_THROW(A.At(3), std::out_of_range);
    BOOST_TEST(A.At(2) == row);
    // Fill
    BOOST_TEST(A.Fill(1) == Matrix<int>({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}));
    BOOST_TEST(A.Fill([](const int& elem){return elem * 2;}) == Matrix<int>({{2, 2, 2}, {2, 2, 2}, {2, 2, 2}}));
    // IsSquare
    BOOST_TEST(A.IsSquare() == false);
    A.Resize(3, 3);
    BOOST_TEST(A.IsSquare());
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
    BOOST_TEST(-B == Matrix<int>(2, 2, {-1, -2, -3, -4}));
    BOOST_TEST(B + A == Matrix<int>(2, 2, {2, 2, 3, 5}));
    BOOST_TEST(B - A == Matrix<int>(2, 2, {0, 2, 3, 3}));
    BOOST_TEST(A + 5 == Matrix<int>(2, 2, {6, 0, 0, 6}));
    BOOST_TEST(A - 5 == Matrix<int>(2, 2, {-4, 0, 0, -4}));
    BOOST_TEST(A * 5 == Matrix<int>({{5, 0}, {0, 5}}));
    BOOST_TEST(B / 2 == Matrix<int>({{0, 1}, {1, 2}}));
}
