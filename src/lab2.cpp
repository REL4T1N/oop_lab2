#include "../include/lab2.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>


// Приватные методы
bool Eleven::isValidDigit(unsigned char digit) const {
    return digit >= 0 && digit <= 10;
}


void Eleven::removeZeroes() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}


unsigned char Eleven::charToDigit(char c) const {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'a' || c == 'A') return 10;
    throw std::invalid_argument("Неверная цифра для 11-ричной системы");
}


char Eleven::digitToChar(unsigned char digit) const {
    if (digit <= 9) return '0' + digit;
    if (digit == 10) return 'A';
    throw std::invalid_argument("Неверное значение цифры");
}


// Конструкторы
Eleven::Eleven() {
    digits.push_back(0);
}


Eleven::Eleven(const size_t &n, unsigned char t) {
    if (!isValidDigit(t)) {
        throw std::invalid_argument("Неверная цифра для 11-ричной системы");
    }

    if (n == 0) {
        digits.push_back(0);
        return;
    }

    digits.resize(n, t);
    removeZeroes();
}


Eleven::Eleven(const std::initializer_list<unsigned char> &t) {
    if (t.size() == 0) {
        digits.push_back(0);
        return;
    }

    for (unsigned char digit : t) {
        if (!isValidDigit(digit)) {
            throw std::invalid_argument("Неверная цифра в списке инициализации");
        }
    }

    for (auto item = t.end() - 1; item >= t.begin(); item--) {
        digits.push_back(*item);
    }
    removeZeroes();
}


Eleven::Eleven(const std::string &t) {
    if (t.empty()) {
        digits.push_back(0);
        return;
    }

    for (char c : t) {
        digits.push_back(charToDigit(c));
    }
    std::reverse(digits.begin(), digits.end());
    removeZeroes();
}


Eleven::Eleven(const Eleven &other) {
    digits = other.digits;
}


Eleven::Eleven(Eleven &&other) noexcept {
    digits = std::move(other.digits);
}


// Методы сравнения
bool Eleven::equals(const Eleven& other) const {
    if (digits.size() != other.digits.size()) return false;

    for (size_t i = 0; i < digits.size(); i++) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}


bool Eleven::less(const Eleven& other) const {
    if (digits.size() < other.digits.size()) return true;
    if (digits.size() > other.digits.size()) return false;

    for (size_t i = digits.size(); i-- > 0; ) {
        if (digits[i] < other.digits[i]) return true;
        if (digits[i] > other.digits[i]) return false;
    }
    return false;
}


bool Eleven::greater(const Eleven& other) const {
    if (digits.size() > other.digits.size()) return true;
    if (digits.size() < other.digits.size()) return false;

    for (size_t i = digits.size(); i-- > 0; ) {
        if (digits[i] > other.digits[i]) return true;
        if (digits[i] < other.digits[i]) return false;
    }
    return false;
}


// Арифметические методы
Eleven Eleven::add(const Eleven& other) const {
    Eleven result;
    result.digits.clear();
    
    size_t max_size = std::max(digits.size(), other.digits.size());
    unsigned char carry = 0;

    for (size_t i = 0; i < max_size || carry != 0; i++) {
        unsigned char digit1 = (i < digits.size()) ? digits[i] : 0;
        unsigned char digit2 = (i < other.digits.size()) ? other.digits[i] : 0;
        unsigned char sum = digit1 + digit2 + carry;

        result.digits.push_back(sum % 11);
        carry = sum / 11;
    }
    return result;
}


Eleven Eleven::subtract(const Eleven& other) const {
    if (less(other)) {
        throw std::invalid_argument("Отрицательный результат вычитания");
    }

    Eleven result;
    result.digits.clear();
    int borrow = 0;

    for (size_t i = 0; i < digits.size(); i++) {
        int digit1 = digits[i];
        int digit2 = (i < other.digits.size()) ? other.digits[i] : 0;
        int diff = digit1 - borrow - digit2;

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


// Преобразование в строку
std::string Eleven::toString() const {
    if (digits.empty()) return "0";

    std::string result;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        result += digitToChar(*it);
    }
    return result;
}