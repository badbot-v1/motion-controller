#include <gtest/gtest.h>
#include "shared/filters/kalman1.hpp"
#include <iostream>

//https://www.youtube.com/watch?v=SIQJaqYVtuE&list=PLX2gX-ftPVXU3oUFNATxGXY90AULiqnWT&index=6
TEST(Kalman_1, cycles)
{
    Kalman1 k(2,68);

    ASSERT_NEAR(70.3333, k.getEstimate( 4, 75), 0.003f);
    ASSERT_NEAR(70.5000, k.getEstimate( 4, 71), 0.003f);
    ASSERT_NEAR(70.4000, k.getEstimate( 4, 70), 0.003f);
    ASSERT_NEAR(71.0000, k.getEstimate( 4, 74), 0.003f);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}