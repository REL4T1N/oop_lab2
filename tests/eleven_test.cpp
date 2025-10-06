#include <gtest/gtest.h>
#include "../include/lab2.h"


// Базовые конструкторы
TEST(ElevenTest, Constructors) {
    Eleven a;
    ASSERT_EQ(a.toString(), "0");
    
    Eleven b(3, 5);
    ASSERT_EQ(b.toString(), "555");
    
    Eleven c(4, 0);
    ASSERT_EQ(c.toString(), "0");
    
    Eleven d(2, 10);
    ASSERT_EQ(d.toString(), "AA");
}


// Специальные конструкторы
TEST(ElevenTest, SpecialConstructors) {
    Eleven a = {5, 10, 2, 1};
    ASSERT_EQ(a.toString(), "5A21");
    
    Eleven b = {0, 0, 1, 2};
    ASSERT_EQ(b.toString(), "12");
    
    Eleven c("3A5");
    ASSERT_EQ(c.toString(), "3A5");
    
    Eleven d("3a5");
    ASSERT_EQ(d.toString(), "3A5");
}


// Копирование и перемещение
TEST(ElevenTest, CopyMove) {
    Eleven num1("A23");
    Eleven num2(num1);
    ASSERT_EQ(num2.toString(), "A23");
    
    Eleven num3(std::move(Eleven("A23")));
    ASSERT_EQ(num3.toString(), "A23");
}


// Математические операции
TEST(ElevenTest, Math) {
    Eleven a("12");
    Eleven b("A3");
    Eleven result1 = a.add(b);
    ASSERT_EQ(result1.toString(), "105");
    
    Eleven c("AA");
    Eleven d("AA");
    Eleven result2 = c.add(d);
    ASSERT_EQ(result2.toString(), "1A9");
    
    Eleven e("A3");
    Eleven f("12");
    Eleven result3 = e.subtract(f);
    ASSERT_EQ(result3.toString(), "91");
    
    // Проверка исключения при вычитании
    ASSERT_THROW(a.subtract(b), std::invalid_argument);
}


// Сравнения
TEST(ElevenTest, Compare) {
    Eleven a("A3");
    Eleven b("12");
    Eleven c("A3");
    
    ASSERT_TRUE(a.equals(c));
    ASSERT_FALSE(a.equals(b));
    ASSERT_TRUE(b.less(a));
    ASSERT_FALSE(a.less(b));
    ASSERT_TRUE(a.greater(b));
    ASSERT_FALSE(b.greater(a));
}


// Граничные случаи
TEST(ElevenTest, EdgeCases) {
    Eleven zero;
    Eleven num("A5");
    
    ASSERT_EQ(zero.add(num).toString(), "A5");
    ASSERT_EQ(num.subtract(zero).toString(), "A5");
    
    Eleven x("A");
    Eleven y("1");
    ASSERT_EQ(x.add(y).toString(), "10");
}


// Обработка ошибок
TEST(ElevenTest, Errors) {
    ASSERT_THROW(Eleven(3, 15), std::invalid_argument);
    ASSERT_THROW(Eleven("12G4"), std::invalid_argument);
    ASSERT_THROW(Eleven({1, 15, 3}), std::invalid_argument);
    
    Eleven a("");
    ASSERT_EQ(a.toString(), "0");
    
    Eleven b("0");
    ASSERT_EQ(b.toString(), "0");
}


// Большие числа
TEST(ElevenTest, BigNumbers) {
    Eleven a("AAAAAAA");
    Eleven b("1");
    Eleven result = a.add(b);
    ASSERT_EQ(result.toString(), "10000000");
}