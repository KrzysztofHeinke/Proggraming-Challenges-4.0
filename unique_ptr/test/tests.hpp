#include <gtest/gtest.h>
#include "../source/unique_ptr.hpp"
#include <algorithm>


TEST(unique_test, reset_method)
{
    my_unique_ptr<int> p = new int;
    p.reset();
    EXPECT_EQ(p.get(), nullptr);
}

TEST(unique_test, move_test)
{
    my_unique_ptr<int> p(new int);
    int *rawPtr = p.get();
    my_unique_ptr<int> p1 = std::move(p);
    EXPECT_EQ(p1.get(), rawPtr);
    EXPECT_EQ(p.get(), nullptr);
}



