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
    bool equals(const Eleven& other) const;
    bool less(const Eleven& other) const;
    bool greater(const Eleven& other) const;

    Eleven add(const Eleven& other) const;
    Eleven subtract(const Eleven& other) const;

    std::string toString() const;
    
};


#endif