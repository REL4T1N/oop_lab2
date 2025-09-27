#include <gtest/gtest.h>
#include "../include/lab2.h"

TEST(ElevenTest, DefaultConstructor) {
    Eleven num;
    ASSERT_EQ(num.size(), 1);
    ASSERT_EQ(num.toString(), "0");
}

TEST(ElevenTest, SizeConstructor) {
    Eleven num(3, 5);
    ASSERT_EQ(num.size(), 3);
    ASSERT_EQ(num.toString(), "555");
}

TEST(ElevenTest, InitializerListConstructor) {
    Eleven num{5, 10, 2, 1};
    ASSERT_EQ(num.toString(), "5A21");
}

TEST(ElevenTest, StringConstructor) {
    Eleven num("3A5");
    ASSERT_EQ(num.toString(), "3A5");
}

TEST(ElevenTest, CopyConstructor) {
    Eleven num1("A23");
    Eleven num2(num1);
    ASSERT_EQ(num2.toString(), "A23");
}

TEST(ElevenTest, AddOperation) {
    Eleven num1("12");
    Eleven num2("A3");
    Eleven result = num1.add(num2);
    ASSERT_EQ(result.toString(), "105");
}

TEST(ElevenTest, SubtractOperation) {
    Eleven num1("A3");
    Eleven num2("12");
    Eleven result = num1.subtract(num2);
    ASSERT_EQ(result.toString(), "91");
}

TEST(ElevenTest, ComparisonOperations) {
    Eleven num1("A3");
    Eleven num2("12");
    Eleven num3("A3");
    
    ASSERT_TRUE(num1.greaterThan(num2));
    ASSERT_TRUE(num2.lessThan(num1));
    ASSERT_TRUE(num1.equals(num3));
}

TEST(ElevenTest, AddAssignOperation) {
    Eleven num1("12");
    Eleven num2("A3");
    Eleven result = num1.addAssign(num2);
    ASSERT_EQ(result.toString(), "105");
}

TEST(ElevenTest, SubtractAssignOperation) {
    Eleven num1("A3");
    Eleven num2("12");
    Eleven result = num1.subtractAssign(num2);
    ASSERT_EQ(result.toString(), "91");
}

TEST(ElevenTest, EdgeCases) {
    Eleven zero;
    Eleven num("A5");
    ASSERT_EQ(zero.add(num).toString(), "A5");
    ASSERT_EQ(num.subtract(zero).toString(), "A5");
    
    Eleven num1("A");
    Eleven num2("1");
    ASSERT_EQ(num1.add(num2).toString(), "10");
}

TEST(ElevenTest, CopyMethod) {
    Eleven num1("A23");
    Eleven num2 = num1.copy();
    ASSERT_EQ(num2.toString(), "A23");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}