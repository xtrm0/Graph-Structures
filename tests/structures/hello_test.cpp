#include <gtest/gtest.h>
#include <bits/stdc++.h>

std::string hello() {
    return "Hello";
}


TEST(Hello, demo)
{
  ASSERT_EQ(hello(),"Hello");
}

TEST(Hello, demo2)
{
  ASSERT_EQ(hello(),"Hello");
}