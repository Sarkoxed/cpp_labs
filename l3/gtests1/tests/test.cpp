#include "../tesrc/lib.hpp"
#include <gtest/gtest.h>
#include <cassert>

using namespace vector;

const size_t size = 10;

TEST(vector, constructors){
//default, int, arr, input
    EXPECT_ANY_THROW(vec<0>(1));
    int a[1] = {1};
    ASSERT_TRUE(vec<5>(1).equal(vec<5>(1, a)));    
}

TEST(vector, append){
    int a[5] = {1,2,3, 4,5};
    int b[6] = {1,2,3,4,5,5};
    vec<6> p(5, a);
    p.append(5);
    ASSERT_TRUE(p.equal(vec<6>(6, b)));
}

TEST(vector, slice){
    int a[5] = {2,3,1,4,5};
    int b[3] = {3,1,4};
    ASSERT_TRUE(vec<5>(5, a).slice(1, 3).equal(vec<5>(3, b)));

}

TEST(vector, add){
    int a[5] = {1,2,3,3,3};
    int b[5] = {3,2,1,1,1};
    int c[5] = {4,4,4,4,4};
    ASSERT_TRUE(vec<5>(5, a).add(vec<5>(5, b)).equal(vec<5>(5, c)));
}

TEST(vector, sort){
    int a[10] = {10,9,5,4,3,5,7,3,2,2};
    int b[10] = {2,2,3,3,4,5,5,7,9,10};   

    vec<10> p(10, a);
    p.sort();
    ASSERT_TRUE(p.equal(vec<10>(10, b)));

}



int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
//
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


