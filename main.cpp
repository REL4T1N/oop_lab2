#include "./include/lab2.h"
#include <iostream>
#include <limits>
#include <vector>

void printMenu() {
    std::cout << "\n=== МЕНЮ СОЗДАНИЯ ЧИСЕЛ ===" << std::endl;
    std::cout << "1. Создать число по умолчанию (0)" << std::endl;
    std::cout << "2. Создать число из n одинаковых цифр" << std::endl;
    std::cout << "3. Демонстрация создания из списка {1, 2, 3}" << std::endl;
    std::cout << "4. Создать число из строки \"123\" или \"A5\"" << std::endl;
    std::cout << "5. Выход" << std::endl;
    std::cout << "Выберите тип создания: ";
}

Eleven createNumber(int choice) {
    switch (choice) {
        case 1: {
            std::cout << "Создано число по умолчанию: ";
            return Eleven();
        }
        case 2: {
            size_t n;
            int t;
            std::cout << "Введите количество цифр: ";
            std::cin >> n;
            std::cout << "Введите цифру (0-9 или 10 для A): ";
            std::cin >> t;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: введите число! Создано число 0." << std::endl;
                return Eleven();
            }
            std::cout << "Создано число из " << n << " цифр " << t << ": ";
            return Eleven(n, static_cast<unsigned char>(t));
        }
        case 3: {
            std::cout << "=== ДЕМОНСТРАЦИЯ INITIALIZER_LIST ===" << std::endl;
            std::cout << "Примеры создания из списков:" << std::endl;
            std::cout << "1. {1, 2, 3} -> 123" << std::endl;
            std::cout << "2. {10, 5, 2} -> A52" << std::endl; 
            std::cout << "3. {0, 0, 1, 2} -> 12" << std::endl;
            std::cout << "Выберите пример (1-3): ";
            
            int example;
            std::cin >> example;
            
            switch (example) {
                case 1:
                    std::cout << "Создано число из списка {1, 2, 3}: ";
                    return Eleven({1, 2, 3});
                case 2:
                    std::cout << "Создано число из списка {10, 5, 2}: ";
                    return Eleven({10, 5, 2});
                case 3:
                    std::cout << "Создано число из списка {0, 0, 1, 2}: ";
                    return Eleven({0, 0, 1, 2});
                default:
                    std::cout << "Неверный выбор! Создано число {1, 2, 3}: ";
                    return Eleven({1, 2, 3});
            }
        }
        case 4: {
            std::string str;
            std::cout << "Введите число в 11-ричной системе (цифры 0-9, A/a для 10): ";
            std::cin >> str;
            std::cout << "Создано число из строки \"" << str << "\": ";
            return Eleven(str);
        }
        default: {
            std::cout << "Неверный выбор! Создано число по умолчанию." << std::endl;
            return Eleven();
        }
    }
}

void demonstrateOperations(const Eleven& a, const Eleven& b) {
    std::cout << "\n=== ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ ===" << std::endl;
    std::cout << "Число A: " << a.toString() << std::endl;
    std::cout << "Число B: " << b.toString() << std::endl;

    std::cout << "\n--- ОПЕРАЦИИ СРАВНЕНИЯ ---" << std::endl;
    std::cout << "A == B: " << (a.equals(b) ? "true" : "false") << std::endl;
    std::cout << "A < B: " << (a.less(b) ? "true" : "false") << std::endl;
    std::cout << "A > B: " << (a.greater(b) ? "true" : "false") << std::endl;
    
    std::cout << "\n--- АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ ---" << std::endl;
    try {
        Eleven sum = a.add(b);
        std::cout << "A + B = " << sum.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка при сложении: " << e.what() << std::endl;
    }
    
    try {
        Eleven diff = a.subtract(b);
        std::cout << "A - B = " << diff.toString() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка при вычитании: " << e.what() << std::endl;
    }

    std::cout << "\n--- ДОПОЛНИТЕЛЬНЫЕ ВОЗМОЖНОСТИ ---" << std::endl;
    Eleven copyA(a);  // Конструктор копирования
    std::cout << "Копия A (конструктор копирования): " << copyA.toString() << std::endl;
    
    Eleven movedB(std::move(Eleven(b)));  // Конструктор перемещения
    std::cout << "Перемещенная копия B: " << movedB.toString() << std::endl;
}

int main() {
    std::cout << "=== ДЕМОНСТРАЦИЯ КЛАССА ELEVEN ===" << std::endl;
    std::cout << "Класс для работы с 11-ричными числами" << std::endl;
    std::cout << "Цифры: 0-9, 10 (представляется как A)" << std::endl;
    
    while (true) {
        std::cout << "\n--- СОЗДАНИЕ ПЕРВОГО ЧИСЛА ---" << std::endl;
        printMenu();
        int choice1;
        std::cin >> choice1;
        
        if (choice1 == 5) break;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;
            continue;
        }
        
        try {
            Eleven num1 = createNumber(choice1);
            std::cout << num1.toString() << std::endl;
            
            std::cout << "\n--- СОЗДАНИЕ ВТОРОГО ЧИСЛА ---" << std::endl;
            printMenu();
            int choice2;
            std::cin >> choice2;
            
            if (choice2 == 5) break;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;
                continue;
            }
            
            Eleven num2 = createNumber(choice2);
            std::cout << num2.toString() << std::endl;
            
            demonstrateOperations(num1, num2);
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка при создании числа: " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.ignore();
        std::cin.get();
    }
    
    std::cout << "Программа завершена." << std::endl;
    return 0;
}