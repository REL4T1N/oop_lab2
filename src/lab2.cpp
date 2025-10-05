/*
Файл lab2.cpp предназначен для раздельной инициализации и реализации методов класса "Eleven".
Именно в данном файле представленна нго инициализация, а именно private параметры и функции и public конструкторы, деструкторы, методы класса,
в дальнейшем возможно добавление сеттера и геттера!
*/


#include "../include/lab2.h"

#include <cstddef>
#include <iostream>
#include <algorithm>
#include <stdexcept>

// 1. Приватные функции
// Функция для валидации значения
bool Eleven::isValidDigit(unsigned char digit) const {
    return (digit >= 0 && digit <= 10);
}

// фнкция для удаления ведущих нулей в реверснутой записи 11-ричного числа
void Eleven::removeZeroes() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

// функция для перевода значения из char в unsigned char
unsigned char Eleven::charToDigit(char c) const {
    if (c >= '0' && c <= '9') {return c - '0';}
    if (c == 'a' || c == 'A') {return 10;}
    throw std::invalid_argument("Invalid digit for base-11");
}

// функия для перевода значения из unsigned char в char
char Eleven::digitToChar(unsigned char digit) const {
    if (digit >= 0 && digit <= 9) {return digit + '0';}
    if (digit == 10) {return 'A';}
    throw std::invalid_argument("Invalid digit value");
}


// 2. Конструкторы
// дефолтный (базовый) конструктор
Eleven::Eleven() {
    digits.push_back(0); 
}

// вектор из n цифр t
Eleven::Eleven(const size_t &n, unsigned char t) {
    if (!isValidDigit(t)) {
        throw std::invalid_argument("Invalid digit for base-11"); 
    }

    if (n == 0) {
        digits.push_back(0);
        return;
    }

    digits.resize(n, t);
    removeZeroes();
}

// Тип std::initializer_list для инициализации списком (скобками {})
Eleven::Eleven(const std::initializer_list<unsigned char> &t) {
    if (t.size() == 0) {
        digits.push_back(0);
        return;
    }

    for (unsigned char digit : t) {
        if (!isValidDigit(digit)) {
            throw std::invalid_argument("Invalid digit in initializer list");
        }
    }

    digits.reserve(t.size());
    // auto заменяет const unsigned char *
    for (auto item = t.end() - 1; item >= t.begin(); item--) {
        digits.push_back(*item);
    }

    removeZeroes();
}

// инициализция простой строкой
Eleven::Eleven(const std::string &t) {
    if (t.empty()) {
        digits.push_back(0);
        return;
    }

    for (char c : t) {
        unsigned char digit = charToDigit(c);
        digits.push_back(digit);
    }

    std::reverse(digits.begin(), digits.end());
    removeZeroes();
}

// конструктор копирования
Eleven::Eleven(const Eleven &other) {
    digits = other.digits;
}

// конструктор перемещения (что-то типо указателя)
Eleven::Eleven(Eleven &&other) noexcept {
    digits = std::move(other.digits); 
}

// 3. Методы класса
// 3.1 Операции сравнения
// функция равенства двух экземпляров
bool Eleven::equals(const Eleven& other) const {
    if (digits.size() != other.digits.size()) {return false;}

    for (size_t i = 0; i < digits.size(); i++) {
        if (digits[i] != other.digits[i]) {return false;}
    }
    return true;
}

// функция сравнения, что выбранный экземпляр класса меньше, переданного в него
bool Eleven::less(const Eleven& other) const {
    if (digits.size() < other.digits.size()) {return true;}
    if (digits.size() > other.digits.size()) {return false;}

    for (size_t i = digits.size(); i-- > 0; ) {
        if (digits[i] < other.digits[i]) {return true;}
        if (digits[i] > other.digits[i]) {return false;}
    }
    return false; // случай когда все элементы равны
}

// функция сравнения, что выбранный экземпляр класса больше, переданного в него
bool Eleven::greater(const Eleven& other) const {
    if (digits.size() > other.digits.size()) {return true;}
    if (digits.size() < other.digits.size()) {return false;}

    for (size_t i = digits.size(); i-- > 0; ) { 
        if (digits[i] > other.digits[i]) {return true;}
        if (digits[i] < other.digits[i]) {return false;}
    }
    return false; // случай когда все элементы равны
}

// 3.2 Арифм. операции
// операцйия сложения (создаём новый экземплроя класса добавив к выбранному переданный)
Eleven Eleven::add(const Eleven& other) const {
    Eleven result;
    result.digits.clear(); // убираем 0
    size_t max_size = std::max(digits.size(), other.digits.size());
    unsigned char carry = 0;

    for (size_t i = 0; i < max_size || carry != 0; i++ ) {
        unsigned char digit1, digit2, sum;
        digit1 = (i < digits.size()) ? digits[i] : 0;
        digit2 = (i < other.digits.size()) ? other.digits[i] : 0;
        sum = digit1 + digit2 + carry;

        result.digits.push_back(sum % 11);
        carry = sum / 11;
    }

    return result;
}

// вычиатеаем переданный экземплря класса из выбранного, создавая новый экземпляр для ответа
Eleven Eleven::subtract(const Eleven& other) const {
    // Если this < other, то результат будет отрицательный
    if (less(other)) {
        throw std::invalid_argument("Result in negative number");
    }

    Eleven result;
    result.digits.clear();
    int borrow = 0;

    for (size_t i = 0; i < digits.size(); i++) {
        int digit1, digit2, diff; 
        digit1 = digits[i];
        digit2 = (i < other.digits.size()) ? other.digits[i] : 0;

        diff = digit1 - borrow - digit2;
        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits.push_back(diff);
    }

    result.removeZeroes();
    return result;
}


// 4. Метод для преобразования в строку
std::string Eleven::toString() const {
    if (digits.empty()) return "0";
    
    std::string result;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        if (*it <= 9) {
            result += ('0' + *it);
        } else if (*it == 10) {
            result += 'A';
        }
    }
    return result;
}