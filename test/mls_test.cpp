#include <gtest/gtest.h>

extern "C"
{
#include "mls.h"
}

namespace
{

constexpr double kTolerance = 1e-10;

double unit_window(int dim, double radius, double *x)
{
    (void)dim;
    (void)radius;
    (void)x;
    return 1.0;
}

TEST(MlsTest, EvaluatesOneDimensionalPolynomialBasis)
{
    double points[] = {0.0};
    double dilations[] = {1.0};
    double values[] = {0.0};
    double x[] = {2.0};
    double basis[4] = {};
    mls_t mls{};

    ASSERT_EQ(0, mls_init(&mls, 1, 1, 3, points, dilations, values, unit_window));
    ASSERT_EQ(0, mls_basis_evaluate(&mls, x, basis));

    EXPECT_DOUBLE_EQ(1.0, basis[0]);
    EXPECT_DOUBLE_EQ(2.0, basis[1]);
    EXPECT_DOUBLE_EQ(4.0, basis[2]);
    EXPECT_DOUBLE_EQ(8.0, basis[3]);
}

TEST(MlsTest, EvaluatesSymmetricMomentMatrix)
{
    double points[] = {-1.0, 0.0, 1.0};
    double dilations[] = {1.0, 1.0, 1.0};
    double values[] = {0.0, 0.0, 0.0};
    double x[] = {0.25};
    double matrix[4] = {};
    mls_t mls{};

    ASSERT_EQ(0, mls_init(&mls, 3, 1, 1, points, dilations, values, unit_window));
    ASSERT_EQ(0, mls_matrix_evaluate(&mls, 1.0, x, matrix));

    EXPECT_NEAR(3.0, matrix[0], kTolerance);
    EXPECT_NEAR(0.0, matrix[1], kTolerance);
    EXPECT_NEAR(0.0, matrix[2], kTolerance);
    EXPECT_NEAR(2.0, matrix[3], kTolerance);
}

TEST(MlsTest, ReproducesLinearFunction)
{
    double points[] = {-1.0, 0.0, 1.0};
    double dilations[] = {1.0, 1.0, 1.0};
    double values[] = {-1.0, 0.0, 1.0};
    double x[] = {0.25};
    mls_t mls{};

    ASSERT_EQ(0, mls_init(&mls, 3, 1, 1, points, dilations, values, unit_window));

    EXPECT_NEAR(0.25, mls_evaluate(&mls, x), kTolerance);
    EXPECT_NEAR(5.0 / 24.0, mls_term_evaluate(&mls, 0, x), kTolerance);
}

class RkpBasisTest : public ::testing::Test
{
protected:
    double points[3] = {-1.0, 0.0, 1.0};
    double dilations[3] = {2.0, 2.0, 2.0};
    double weights[3] = {1.0, 1.0, 1.0};
    double values[3] = {-1.0, 0.0, 1.0};
    rkp_t rkp{};

    void SetUp() override
    {
        ASSERT_EQ(0, rkp_init(&rkp, 3, 1, 1, points, dilations, weights, values,
                              unit_window, 2.0));
    }

    void TearDown() override
    {
        rkp_free(&rkp);
    }

    void ExpectLinearReproduction(bool scaled = false)
    {
        for (int node = 0; node < 3; ++node)
        {
            const double interpolated =
                scaled ? rkp_evaluate_node_scaled(&rkp, node)
                       : rkp_evaluate_node(&rkp, node);
            EXPECT_NEAR(points[node], interpolated, kTolerance)
                << "at node " << node;
        }
    }
};

TEST_F(RkpBasisTest, GeneratesBasisThatReproducesLinearData)
{
    ASSERT_EQ(0, rkp_basis_generate(&rkp));

    ExpectLinearReproduction();
}

TEST_F(RkpBasisTest, ScaledBasisGeneratorsReproduceLinearData)
{
    ASSERT_EQ(0, rkp_basis_generate_scaled(&rkp));
    ExpectLinearReproduction(true);
}

TEST_F(RkpBasisTest, WaveletBasisReproducesLinearDerivative)
{
    ASSERT_EQ(0, rkp_wavelet_basis_generate(&rkp));

    for (int node = 0; node < 3; ++node)
        EXPECT_NEAR(1.0, rkp_wavelet_evaluate_node(&rkp, 0, node), kTolerance)
            << "at node " << node;
}

} // namespace
