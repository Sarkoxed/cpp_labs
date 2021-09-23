#include "gtest/gtest.h"
#include "../src/lib.hpp"

#include <cassert>

using namespace hypo;

TEST(pair, pairff){
    hypocycloid a;
    hypocycloid b(2.0, 4.0);
    hypocycloid c(2.0, 4.0, 3.2);
    hypocycloid d(2, 4.2);

    ASSERT_EQ(pair<double, double>(1.0, 0.0),  a.get_point(32.0));
    ASSERT_EQ(pair<double, double>(1.0, sqrt(3)*3.0), b.get_point(M_PI / 3.0));

}


int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
