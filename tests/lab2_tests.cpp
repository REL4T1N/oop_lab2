#include <gtest/gtest.h>
#include "../include/lab2.h"

// Тесты для класса Eleven (11-ричная система счисления)

// Тест конструктора по умолчанию - должен создавать число 0
TEST(ElevenTest, DefaultConstructor) {
    Eleven num;
    ASSERT_EQ(num.toString(), "0");
}

// Тест конструктора с размером и значением - создание числа из повторяющихся цифр
TEST(ElevenTest, SizeConstructor) {
    Eleven num(3, 5);
    ASSERT_EQ(num.toString(), "555");
}

// Тест конструктора с размером и нулевым значением - должен создавать число 0
TEST(ElevenTest, SizeConstructorWithZero) {
    Eleven num(4, 0);
    ASSERT_EQ(num.toString(), "0");
}

// Тест конструктора с размером и значением 10 (цифра A в 11-ричной системе)
TEST(ElevenTest, SizeConstructorWithA) {
    Eleven num(2, 10);
    ASSERT_EQ(num.toString(), "AA");
}

// Тест конструктора со списком инициализации - создание числа из набора цифр
TEST(ElevenTest, InitializerListConstructor) {
    Eleven num = {5, 10, 2, 1};
    ASSERT_EQ(num.toString(), "5A21");
}

// Тест конструктора со списком инициализации с ведущими нулями - нули должны отбрасываться
TEST(ElevenTest, InitializerListWithLeadingZeros) {
    Eleven num = {0, 0, 1, 2};
    ASSERT_EQ(num.toString(), "12");
}

// Тест конструктора из строки - создание числа из строкового представления
TEST(ElevenTest, StringConstructor) {
    Eleven num("3A5");
    ASSERT_EQ(num.toString(), "3A5");
}

// Тест конструктора из строки с буквами в нижнем регистре - должен преобразовывать в верхний регистр
TEST(ElevenTest, StringConstructorWithLowercase) {
    Eleven num("3a5");
    ASSERT_EQ(num.toString(), "3A5");
}

// Тест конструктора копирования - создание копии объекта
TEST(ElevenTest, CopyConstructor) {
    Eleven num1("A23");
    Eleven num2(num1);
    ASSERT_EQ(num2.toString(), "A23");
}

// Тест конструктора перемещения - перемещение ресурсов из одного объекта в другой
TEST(ElevenTest, MoveConstructor) {
    Eleven num1("A23");
    Eleven num2(std::move(num1));
    ASSERT_EQ(num2.toString(), "A23");
}

// Тест операции сложения двух чисел
TEST(ElevenTest, AddOperation) {
    Eleven num1("12");
    Eleven num2("A3");
    Eleven result = num1.add(num2);
    ASSERT_EQ(result.toString(), "105");
}

// Тест операции сложения с переносом через разряд
TEST(ElevenTest, AddOperationWithCarry) {
    Eleven num1("AA");
    Eleven num2("AA");
    Eleven result = num1.add(num2);
    ASSERT_EQ(result.toString(), "1A9");
}

// Тест операции вычитания двух чисел
TEST(ElevenTest, SubtractOperation) {
    Eleven num1("A3");
    Eleven num2("12");
    Eleven result = num1.subtract(num2);
    ASSERT_EQ(result.toString(), "91");
}

// Тест операции вычитания равных чисел - должен возвращать 0
TEST(ElevenTest, SubtractEqualNumbers) {
    Eleven num1("123");
    Eleven num2("123");
    Eleven result = num1.subtract(num2);
    ASSERT_EQ(result.toString(), "0");
}

// Тест операции вычитания когда результат отрицательный - должно выбрасываться исключение
TEST(ElevenTest, SubtractThrowsWhenNegative) {
    Eleven num1("12");
    Eleven num2("A3");
    ASSERT_THROW(num1.subtract(num2), std::invalid_argument);
}

// Тест операции сравнения на равенство
TEST(ElevenTest, EqualsComparison) {
    Eleven num1("A3");
    Eleven num2("A3");
    Eleven num3("12");
    
    ASSERT_TRUE(num1.equals(num2));
    ASSERT_FALSE(num1.equals(num3));
}

// Тест операции сравнения "меньше"
TEST(ElevenTest, LessComparison) {
    Eleven num1("12");
    Eleven num2("A3");
    
    ASSERT_TRUE(num1.less(num2));
    ASSERT_FALSE(num2.less(num1));
}

// Тест операции сравнения "больше"
TEST(ElevenTest, GreaterComparison) {
    Eleven num1("A3");
    Eleven num2("12");
    
    ASSERT_TRUE(num1.greater(num2));
    ASSERT_FALSE(num2.greater(num1));
}

// Тест граничных случаев и особых ситуаций
TEST(ElevenTest, EdgeCases) {
    Eleven zero;
    Eleven num("A5");
    
    // 0 + A5 = A5
    ASSERT_EQ(zero.add(num).toString(), "A5");
    // A5 - 0 = A5
    ASSERT_EQ(num.subtract(zero).toString(), "A5");
    
    // A + 1 = 10
    Eleven num1("A");
    Eleven num2("1");
    ASSERT_EQ(num1.add(num2).toString(), "10");
}

// Тест обработки недопустимых цифр - должны выбрасываться исключения
TEST(ElevenTest, InvalidDigitThrows) {
    ASSERT_THROW(Eleven(3, 15), std::invalid_argument);
    ASSERT_THROW(Eleven("12G4"), std::invalid_argument);
    ASSERT_THROW(Eleven({1, 15, 3}), std::invalid_argument);
}

// Тест конструктора из пустой строки - должен создавать число 0
TEST(ElevenTest, EmptyStringConstructor) {
    Eleven num("");
    ASSERT_EQ(num.toString(), "0");
}

// Тест конструктора из строки "0" - должен создавать число 0
TEST(ElevenTest, SingleZeroString) {
    Eleven num("0");
    ASSERT_EQ(num.toString(), "0");
}

// Тест операций с большими числами
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