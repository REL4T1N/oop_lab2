#include "../include/lab2.h"
#include <algorithm>
#include <stdexcept>

// Проверка валидности цифры
bool Eleven::isValidDigit(unsigned char digit) const {
    return digit >= 0 && digit <= 10;
}

// Конвертация char в цифру
unsigned char Eleven::charToDigit(char c) const {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c == 'A' || c == 'a') {
        return 10;
    }
    throw std::invalid_argument("Invalid digit for eleven number system");
}

// Конвертация цифры в char
char Eleven::digitToChar(unsigned char digit) const {
    if (digit < 10) {
        return '0' + digit;
    } else if (digit == 10) {
        return 'A';
    }
    throw std::invalid_argument("Invalid digit value");
}

// Удаление ведущих нулей
void Eleven::removeLeadingZeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

// Конструкторы
Eleven::Eleven() : digits{0} {}

Eleven::Eleven(const size_t &n, unsigned char t) {
    if (n == 0) {
        throw std::invalid_argument("Size cannot be zero");
    }
    if (!isValidDigit(t)) {
        throw std::invalid_argument("Invalid digit for eleven number system");
    }
    digits = std::vector<unsigned char>(n, t);
    removeLeadingZeros();
}

Eleven::Eleven(const std::initializer_list<unsigned char> &t) {
    if (t.size() == 0) {
        digits = {0};
        return;
    }
    
    // Цифры идут от СТАРШИХ к МЛАДШИМ в initializer list
    digits.assign(t.begin(), t.end());
    // Проверка валидности цифр
    for (unsigned char digit : digits) {
        if (!isValidDigit(digit)) {
            throw std::invalid_argument("Invalid digit for eleven number system");
        }
    }
    // Разворачиваем, чтобы младшая цифра была в начале
    std::reverse(digits.begin(), digits.end());
    removeLeadingZeros();
}

Eleven::Eleven(const std::string &t) {
    if (t.empty()) {
        digits = {0};
        return;
    }
    
    for (auto it = t.rbegin(); it != t.rend(); ++it) {
        digits.push_back(charToDigit(*it));
    }
    removeLeadingZeros();
}

Eleven::Eleven(const Eleven& other) : digits(other.digits) {}

Eleven::Eleven(Eleven&& other) noexcept : digits(std::move(other.digits)) {
    other.digits = {0};
}

Eleven::~Eleven() noexcept {}

// Базовые методы
size_t Eleven::size() const {
    return digits.size();
}

std::string Eleven::toString() const {
    if (digits.empty()) return "0";
    
    std::string result;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        result += digitToChar(*it);
    }
    return result;
}

bool Eleven::equals(const Eleven& other) const {
    return digits == other.digits;
}

bool Eleven::lessThan(const Eleven& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false; // равны
}

bool Eleven::greaterThan(const Eleven& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() > other.digits.size();
    }
    
    for (int i = digits.size() - 1; i >= 0; --i) {
        if (digits[i] != other.digits[i]) {
            return digits[i] > other.digits[i];
        }
    }
    return false; // равны
}

// Арифметические операции
Eleven Eleven::add(const Eleven& other) const {
    std::vector<unsigned char> result;
    size_t maxSize = std::max(digits.size(), other.digits.size());
    unsigned char carry = 0;
    
    for (size_t i = 0; i < maxSize || carry; ++i) {
        unsigned char digit1 = (i < digits.size()) ? digits[i] : 0;
        unsigned char digit2 = (i < other.digits.size()) ? other.digits[i] : 0;
        
        unsigned char sum = digit1 + digit2 + carry;
        carry = sum / 11;
        result.push_back(sum % 11);
    }
    
    Eleven temp;
    temp.digits = result;
    return temp;
}

Eleven Eleven::subtract(const Eleven& other) const {
    if (lessThan(other)) {
        throw std::invalid_argument("Cannot subtract larger number from smaller");
    }
    
    if (equals(other)) {
        return Eleven();
    }
    
    std::vector<unsigned char> result;
    int borrow = 0;
    
    for (size_t i = 0; i < digits.size(); ++i) {
        int diff = digits[i] - borrow;
        if (i < other.digits.size()) {
            diff -= other.digits[i];
        }
        
        if (diff < 0) {
            diff += 11;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back(static_cast<unsigned char>(diff));
    }
    
    Eleven temp;
    temp.digits = result;
    temp.removeLeadingZeros();
    return temp;
}

Eleven Eleven::copy() const {
    return Eleven(*this);
}

// Операции с присваиванием
Eleven Eleven::addAssign(const Eleven& other) const {
    return add(other);
}

Eleven Eleven::subtractAssign(const Eleven& other) const {
    return subtract(other);
}