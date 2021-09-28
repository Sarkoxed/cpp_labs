#include <gtest/gtest.h>
#include "../tesrc/lib.hpp"
#include <cassert>

//ASSERT_TRUE(condition);
//ASSERT_FALSE(condition);
//ASSERT_EQ(expected, actual); — =
//ASSERT_NE(val1, val2); — !=
//ASSERT_LT(val1, val2); — <
//ASSERT_LE(val1, val2); — <=
//ASSERT_GT(val1, val2); — >
//ASSERT_GE(val1, val2); — >=
//ASSERT_STREQ(expected_str, actual_str);
//ASSERT_STRNE(str1, str2);
//ASSERT_STRCASEEQ(expected_str, actual_str); — регистронезависимо
//ASSERT_STRCASENE(str1, str2); — регистронезависимо
//ASSERT_THROW(statement, exception_type);
//ASSERT_ANY_THROW(statement);
//ASSERT_NO_THROW(statement)
//ASSERT_PREDN(pred, val1, val2, ..., valN); — N <= 5
//ASSERT_PRED_FORMATN(pred_format, val1, val2, ..., valN
//ASSERT_FLOAT_EQ(expected, actual); — неточное сравнение float
//ASSERT_DOUBLE_EQ(expected, actual); — неточное сравнение double
//ASSERT_NEAR(val1, val2, abs_error); — разница между val1 и val2 не превышает
//SUCCEED();
//FAIL();
//ADD_FAILURE();
//ADD_FAILURE_AT(«file_path», line_number);


using namespace curve;

TEST(curve, curve_point){
    hypocycloid a;
    hypocycloid b(2.0, 4.0);
    hypocycloid c(2.0, 4.0, 3.2);
    hypocycloid d(2, 4.2);
    double x = a.get_point(32.0).x(), y = a.get_point(32.0).y();

    EXPECT_DOUBLE_EQ(1.0, x);
    EXPECT_DOUBLE_EQ(0.0, y);
    EXPECT_DOUBLE_EQ(sqrt(3)*3.0, b.get_point(pi / 3.0).y());
    ASSERT_ANY_THROW(hypocycloid(-1.0, 1.0, 1.0));
    ASSERT_ANY_THROW(hypocycloid(0, 2.0, 3.0));
    ASSERT_ANY_THROW(a.set_d(-1.0)); 
    ASSERT_ANY_THROW(a.set_r(-1.0));
    ASSERT_ANY_THROW(a.set_k(-1.0));
    
    EXPECT_DOUBLE_EQ(2.0 , b.get_rs().x()); 
    EXPECT_DOUBLE_EQ(8.0,  c.get_rs().y());

    EXPECT_DOUBLE_EQ(pi * 24, b.sectorial_area());
}


int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
