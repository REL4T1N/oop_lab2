/*
Файл lab2.h предназначен для раздельной инициализации и реализации методов класса "Eleven".
Именно в данном файле представленна нго инициализация, а именно private параметры и функции и public конструкторы, деструкторы, методы класса,
в дальнейшем возможно добавление сеттера и геттера!
*/


#ifndef LAB2_H
#define LAB2_H

#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Eleven {
private:
    std::vector<unsigned char> digits;
    
    bool isValidDigit(unsigned char digit) const;
    void removeZeroes();
    unsigned char charToDigit(char c) const;
    char digitToChar(unsigned char digit) const;

public:
    // 1. Конструкторы
    Eleven();

    Eleven(const size_t &n, unsigned char t = 0);
    Eleven(const std::initializer_list<unsigned char> &t);
    Eleven(const std::string &t);

    Eleven(const Eleven &other);
    Eleven(Eleven &&other) noexcept; // && - ссылка на rValue
    virtual ~Eleven() noexcept = default; // виртуальный деструктор

    // 2. Методы класса
    // Операции сравнения (равенство, меньше, больше)
    bool equals(const Eleven& other) const;
    bool less(const Eleven& other) const;
    bool greater(const Eleven& other) const;
    // Арифметичсеукоеи операции (сложение, вычитание)
    Eleven add(const Eleven& other) const;
    Eleven subtract(const Eleven& other) const;
    // Метод для представления 11ричного числа в строковом виде
    std::string toString() const;
    
};


#endif