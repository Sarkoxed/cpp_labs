#include "../tesrc/lib.hpp"
#include <gtest/gtest.h>
#include <cassert>
#include <random>
#include <algorithm>
#include <iostream>
using namespace vector;
int randint(int a, int b){
    return static_cast<int>((b-a) * static_cast<double>(rand()) / RAND_MAX + a);
}

int n = randint(1, 100);
TEST(vector, constructors){
    int x = randint(-100, 100);     
    int nig = randint(-100, -10);
    int a[n], b[n];
    for(int i = 0; i < n; i++){
        a[i] = x;
        b[i] = randint(-100, 100);
    }
    EXPECT_ANY_THROW(vec(-199));
    EXPECT_ANY_THROW(vec(nig, 1));
    EXPECT_ANY_THROW(vec(nig, a));
    
    EXPECT_NO_THROW(vec(static_cast<int>(n)));
    ASSERT_TRUE(vec(n).size() == n);
    ASSERT_TRUE(vec(n) == vec(n, 0));

    ASSERT_TRUE(vec(n, x) == vec(n, a));
    
    vec z(n, b);
    ASSERT_TRUE(z[n / 2] == b[n / 2]);
    ASSERT_TRUE(z[n / 3] == b[n / 3]);
    ASSERT_TRUE(z == z);
}

TEST(vector, copymove){
    int a[n];
    for(int i = 0; i < n; i++){
        a[i] = randint(-100, 100);
    }
    vec m(n, a);
    vec k(m);
    vec z = m;
    vec r = std::move(m); // move constructor
    vec u = r; // implicit copy constructor
    u = k; // copy assignment
    ASSERT_TRUE(r[n / 3] == a[n / 3] && r[n/3] == z[n/3]);
    r = vec(n - randint(0, n-1), a);  // move assignment
    ASSERT_TRUE(r[0] == a[0]);
}


TEST(vector, overloaded){
    int a[n];
    for(int i = 0; i < n; i++){
        a[i] = randint(-100, 100);
    }
    vec z(n, a);
    EXPECT_ANY_THROW(z[n+2]);
    EXPECT_ANY_THROW(z[-4]);
    vec m(n, a);
    EXPECT_TRUE(m == z);
    vec r(n / 2, 2);
    EXPECT_TRUE(m != r);

    EXPECT_TRUE(z);
    EXPECT_FALSE(vec(0));
}

TEST(vector, adding){
    int a[n],b[n],c[n],d[n];
    for(int i = 0; i < n; i++){
        a[i] = randint(-100, 100);
        b[i] = randint(-100, 100);
        c[i] = a[i] + b[i];
        d[i] = 2*c[i];
    }
    vec r(n, a), v(n, b);
    vec z = r + v; 
    ASSERT_TRUE(z == vec(n, c));
    r += v;
    ASSERT_TRUE(r == vec(n, c));
    z = r + r;
    r += r;
    ASSERT_TRUE(r == vec(n, d));
    ASSERT_TRUE(z == vec(n, d));
    const vec k(r);
}

TEST(vector, append){
    int k = n - randint(n / 2, n);
    int a[n];
    for(int i = 0; i < k; i++){
        a[i] = randint(-100,100);
    }
    vec z(k, a);
    for(int i = k; i < n; i++){
        int f=  randint(-100, 100);
        z.append(f);
        a[i] =f;
    }

    ASSERT_TRUE(z == vec(n, a));
}

TEST(vector, slice){
    int a[n];
    for(int i = 0; i < n; i++){
        a[i] = randint(-100, 100);
    }
    vec z(n, a);
    EXPECT_ANY_THROW(z.slice(-1, 100));
    EXPECT_ANY_THROW(z.slice(randint(1, n), 2*n));
    int k = randint(1, n);
    int m = (n - k) / 2;
    ASSERT_TRUE(z.slice(k, m) == vec(m, a + k));
}

TEST(vector, sort){
    int a[n];
    for(int i = 0; i < n; i++){
        a[i] = randint(-100, 100);
    }
    vec z(n, a);
    std::sort(a, a+n);
    z.sort();
    ASSERT_TRUE(z == vec(n, a));

}
int main(){
    srand(time(0));
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


