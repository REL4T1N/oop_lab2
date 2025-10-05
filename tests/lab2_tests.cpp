#include <gtest/gtest.h>
#include "../include/lab2.h"

TEST(ElevenTest, DefaultConstructor) {
    Eleven num;
    ASSERT_EQ(num.toString(), "0");
}

TEST(ElevenTest, SizeConstructor) {
    Eleven num(3, 5);
    ASSERT_EQ(num.toString(), "555");
}

TEST(ElevenTest, SizeConstructorWithZero) {
    Eleven num(4, 0);
    ASSERT_EQ(num.toString(), "0");
}

TEST(ElevenTest, SizeConstructorWithA) {
    Eleven num(2, 10);
    ASSERT_EQ(num.toString(), "AA");
}

TEST(ElevenTest, InitializerListConstructor) {
    Eleven num = {5, 10, 2, 1};
    ASSERT_EQ(num.toString(), "5A21");
}

TEST(ElevenTest, InitializerListWithLeadingZeros) {
    Eleven num = {0, 0, 1, 2};
    ASSERT_EQ(num.toString(), "12");
}

TEST(ElevenTest, StringConstructor) {
    Eleven num("3A5");
    ASSERT_EQ(num.toString(), "3A5");
}

TEST(ElevenTest, StringConstructorWithLowercase) {
    Eleven num("3a5");
    ASSERT_EQ(num.toString(), "3A5");
}

TEST(ElevenTest, CopyConstructor) {
    Eleven num1("A23");
    Eleven num2(num1);
    ASSERT_EQ(num2.toString(), "A23");
}

TEST(ElevenTest, MoveConstructor) {
    Eleven num1("A23");
    Eleven num2(std::move(num1));
    ASSERT_EQ(num2.toString(), "A23");
}

TEST(ElevenTest, AddOperation) {
    Eleven num1("12");
    Eleven num2("A3");
    Eleven result = num1.add(num2);
    ASSERT_EQ(result.toString(), "105");
}

TEST(ElevenTest, AddOperationWithCarry) {
    Eleven num1("AA");
    Eleven num2("AA");
    Eleven result = num1.add(num2);
    ASSERT_EQ(result.toString(), "1A9");
}

TEST(ElevenTest, SubtractOperation) {
    Eleven num1("A3");
    Eleven num2("12");
    Eleven result = num1.subtract(num2);
    ASSERT_EQ(result.toString(), "91");
}

TEST(ElevenTest, SubtractEqualNumbers) {
    Eleven num1("123");
    Eleven num2("123");
    Eleven result = num1.subtract(num2);
    ASSERT_EQ(result.toString(), "0");
}

TEST(ElevenTest, SubtractThrowsWhenNegative) {
    Eleven num1("12");
    Eleven num2("A3");
    ASSERT_THROW(num1.subtract(num2), std::invalid_argument);
}

TEST(ElevenTest, EqualsComparison) {
    Eleven num1("A3");
    Eleven num2("A3");
    Eleven num3("12");
    
    ASSERT_TRUE(num1.equals(num2));
    ASSERT_FALSE(num1.equals(num3));
}

TEST(ElevenTest, LessComparison) {
    Eleven num1("12");
    Eleven num2("A3");
    
    ASSERT_TRUE(num1.less(num2));
    ASSERT_FALSE(num2.less(num1));
}

TEST(ElevenTest, GreaterComparison) {
    Eleven num1("A3");
    Eleven num2("12");
    
    ASSERT_TRUE(num1.greater(num2));
    ASSERT_FALSE(num2.greater(num1));
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

TEST(ElevenTest, InvalidDigitThrows) {
    ASSERT_THROW(Eleven(3, 15), std::invalid_argument);
    ASSERT_THROW(Eleven("12G4"), std::invalid_argument);
    ASSERT_THROW(Eleven({1, 15, 3}), std::invalid_argument);
}

TEST(ElevenTest, EmptyStringConstructor) {
    Eleven num("");
    ASSERT_EQ(num.toString(), "0");
}

TEST(ElevenTest, SingleZeroString) {
    Eleven num("0");
    ASSERT_EQ(num.toString(), "0");
}

TEST(ElevenTest, LargeNumbers) {
    Eleven num1("AAAAAAA");   
    Eleven num2("1");
    Eleven result = num1.add(num2);
    ASSERT_EQ(result.toString(), "10000000"); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}