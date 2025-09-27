#ifndef LAB2_H
#define LAB2_H

#include <string>
#include <vector>
#include <stdexcept>

class Eleven {
private:
    std::vector<unsigned char> digits; // младшая цифра по младшему индексу
    void removeLeadingZeros();
    bool isValidDigit(unsigned char digit) const;
    unsigned char charToDigit(char c) const;
    char digitToChar(unsigned char digit) const;

public:
    // Конструкторы
    Eleven();
    Eleven(const size_t &n, unsigned char t = 0);
    Eleven(const std::initializer_list<unsigned char> &t);
    Eleven(const std::string &t);
    Eleven(const Eleven& other);
    Eleven(Eleven&& other) noexcept;
    
    // Деструктор
    virtual ~Eleven() noexcept;

    // Базовые методы
    size_t size() const;
    std::string toString() const;
    bool equals(const Eleven& other) const;
    bool lessThan(const Eleven& other) const;
    bool greaterThan(const Eleven& other) const;

    // Арифметические операции
    Eleven add(const Eleven& other) const;
    Eleven subtract(const Eleven& other) const;
    Eleven copy() const;

    // Операции с присваиванием (возвращают новый объект)
    Eleven addAssign(const Eleven& other) const;
    Eleven subtractAssign(const Eleven& other) const;

    // Вспомогательные методы для тестирования
    const std::vector<unsigned char>& getDigits() const { return digits; }
};

#endif