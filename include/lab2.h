#ifndef LAB2_H
#define LAB2_H

#include <iostream>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Eleven {
private:
    size_t _size;
    unsigned char* _digits;
    
    bool isValidDigit(unsigned char digit) const;
    void removeZeroes();
    unsigned char charToDigit(char c) const;
    char digitToChar(unsigned char digit) const;
    void _copyFrom(const Eleven& other);
    void _free();

public:
    // 1. Конструкторы
    Eleven();
    Eleven(const size_t &n, unsigned char t = 0);
    Eleven(const std::initializer_list<unsigned char> &t);
    Eleven(const std::string &t);

    // 2. Правило пяти
    Eleven(const Eleven &other);
    Eleven(Eleven &&other) noexcept;
    // Eleven& operator=(const Eleven& other); // Перегрузка оператора 
    // Eleven& operator=(Eleven&& other) noexcept; // Перегрузка оператора
    virtual ~Eleven() noexcept;

    // 3. Методы класса
    bool equals(const Eleven& other) const;
    bool less(const Eleven& other) const;
    bool greater(const Eleven& other) const;
    Eleven add(const Eleven& other) const;
    Eleven subtract(const Eleven& other) const;
    std::string toString() const;
    
    // 4. Вспомогательные методы для отладки
    size_t size() const { return _size; }
    const unsigned char* data() const { return _digits; }
};

#endif