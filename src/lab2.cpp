#include "../include/lab2.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Приватные методы
bool Eleven::isValidDigit(unsigned char digit) const {
    return digit >= 0 && digit <= 10;
}


void Eleven::removeZeroes() {
    if (_size == 0) {
        return;
    }
    
    // Находим первую ненулевую цифру (с конца, так как старшие разряды в конце)
    size_t new_size = _size;
    for (size_t i = _size - 1; i > 0; i--) {
        if (_digits[i] == 0) {
            new_size--;
        } else {
            break;
        }
    }
    
    if (new_size != _size) {
        unsigned char* new_digits = new unsigned char[new_size];
        for (size_t i = 0; i < new_size; i++) {
            new_digits[i] = _digits[i];
        }
        delete[] _digits;
        _digits = new_digits;
        _size = new_size;
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


void Eleven::_copyFrom(const Eleven& other) {
    _size = other._size;
    _digits = new unsigned char[_size];
    for (size_t i = 0; i < _size; i++) {
        _digits[i] = other._digits[i];
    }
}


void Eleven::_free() {
    if (_digits != nullptr) {
        delete[] _digits;
        _digits = nullptr;
    }
    _size = 0;
}



// Конструкторы
Eleven::Eleven() : _size(1), _digits(new unsigned char[1]{0}) {}


Eleven::Eleven(const size_t &n, unsigned char t) {
    if (!isValidDigit(t)) {
        throw std::invalid_argument("Неверная цифра для 11-ричной системы");
    }
    if (n == 0) {
        _size = 1;
        _digits = new unsigned char[1]{0};
        return;
    }

    _size = n;
    _digits = new unsigned char[_size];
    for (size_t i = 0; i < _size; i++) {
        _digits[i] = t;
    }
    removeZeroes();
}


Eleven::Eleven(const std::initializer_list<unsigned char> &t) {
    if (t.size() == 0) {
        _size = 1;
        _digits = new unsigned char[1]{0};
        return;
    }
    for (unsigned char digit : t) {
        if (!isValidDigit(digit)) {
            throw std::invalid_argument("Неверная цифра в списке инициализации");
        }
    }

    _size = t.size();
    _digits = new unsigned char[_size];
    size_t i = 0;
    for (auto item = t.end() - 1; item >= t.begin(); item--) {
        _digits[i++] = *item;
        if (i >= _size) break;
    }
    removeZeroes();
}


Eleven::Eleven(const std::string &t) {
    if (t.empty()) {
        _size = 1;
        _digits = new unsigned char[1]{0};
        return;
    }

    _size = t.length();
    _digits = new unsigned char[_size];
    for (size_t i = 0; i < _size; i++) {
        _digits[i] = charToDigit(t[_size - 1 - i]);
    }
    removeZeroes();
}


// Правило пяти
Eleven::Eleven(const Eleven &other) {
    _copyFrom(other);
}


Eleven::Eleven(Eleven &&other) noexcept 
    : _size(other._size), _digits(other._digits) {
    other._size = 0;
    other._digits = nullptr;
}


/* Перегрузка оператора
Eleven& Eleven::operator=(const Eleven& other) {
    if (this != &other) {
        _free();
        _copyFrom(other);
    }
    return *this;
}


Перегрузка оператора
Eleven& Eleven::operator=(Eleven&& other) noexcept {
    if (this != &other) {
        _free();
        _size = other._size;
        _digits = other._digits;
        other._size = 0;
        other._digits = nullptr;
    }
    return *this;
}
*/

Eleven::~Eleven() noexcept {
    _free();
}


// Методы сравнения
bool Eleven::equals(const Eleven& other) const {
    if (_size != other._size) return false;

    for (size_t i = 0; i < _size; i++) {
        if (_digits[i] != other._digits[i]) return false;
    }
    return true;
}


bool Eleven::less(const Eleven& other) const {
    if (_size < other._size) return true;
    if (_size > other._size) return false;

    for (size_t i = _size; i-- > 0; ) {
        if (_digits[i] < other._digits[i]) return true;
        if (_digits[i] > other._digits[i]) return false;
    }
    return false;
}


bool Eleven::greater(const Eleven& other) const {
    if (_size > other._size) return true;
    if (_size < other._size) return false;

    for (size_t i = _size; i-- > 0; ) {
        if (_digits[i] > other._digits[i]) return true;
        if (_digits[i] < other._digits[i]) return false;
    }
    return false;
}


// Арифметические методы
Eleven Eleven::add(const Eleven& other) const {
    Eleven result;
    result._free(); // Освобождаем память от конструктора по умолчанию
    
    size_t max_size = std::max(_size, other._size);
    unsigned char carry = 0;
    size_t result_size = 0;
    
    // Временный массив для результата (максимально возможный размер)
    unsigned char* temp = new unsigned char[max_size + 1]{0};

    for (size_t i = 0; i < max_size || carry != 0; i++) {
        unsigned char digit1 = (i < _size) ? _digits[i] : 0;
        unsigned char digit2 = (i < other._size) ? other._digits[i] : 0;
        unsigned char sum = digit1 + digit2 + carry;

        temp[i] = sum % 11;
        carry = sum / 11;
        result_size = i + 1;
    }

    // Создаем финальный массив результата
    result._size = result_size;
    result._digits = new unsigned char[result_size];
    for (size_t i = 0; i < result_size; i++) {
        result._digits[i] = temp[i];
    }
    
    delete[] temp;
    result.removeZeroes();
    return result;
}


Eleven Eleven::subtract(const Eleven& other) const {
    if (less(other)) {
        throw std::invalid_argument("Отрицательный результат вычитания");
    }

    Eleven result;
    result._free();
    
    result._size = _size;
    result._digits = new unsigned char[_size]{0};
    
    int borrow = 0;

    for (size_t i = 0; i < _size; i++) {
        int digit1 = _digits[i];
        int digit2 = (i < other._size) ? other._digits[i] : 0;
        int diff = digit1 - borrow - digit2;

        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result._digits[i] = diff;
    }
    result.removeZeroes();
    return result;
}


// Преобразование в строку
std::string Eleven::toString() const {
    if (_size == 0) return "0";

    std::string result;
    for (size_t i = _size; i-- > 0; ) {
        result += digitToChar(_digits[i]);
    }
    return result;
}