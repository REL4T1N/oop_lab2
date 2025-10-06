#include "./include/lab2.h"
#include <iostream>
#include <string>

int main() {
    std::string str1, str2;
    std::cout << "Введите первое число: ";
    std::cin >> str1;
    std::cout << "Введите второе число: ";
    std::cin >> str2;
    
    try {
        Eleven a(str1);
        Eleven b(str2);
        
        std::cout << "Число A: " << a.toString() << std::endl;
        std::cout << "Число B: " << b.toString() << std::endl;
        
        std::cout << "A == B: " << (a.equals(b) ? "true" : "false") << std::endl;
        std::cout << "A < B: " << (a.less(b) ? "true" : "false") << std::endl;
        std::cout << "A > B: " << (a.greater(b) ? "true" : "false") << std::endl;
        
        Eleven sum = a.add(b);
        std::cout << "A + B = " << sum.toString() << std::endl;
        
        try {
            Eleven diff = a.subtract(b);
            std::cout << "A - B = " << diff.toString() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "A - B: ошибка - " << e.what() << std::endl;
        }
        
        Eleven copyA(a);
        std::cout << "Копия A: " << copyA.toString() << std::endl;
        
        Eleven movedB(std::move(Eleven(b)));
        std::cout << "Перемещенная копия B: " << movedB.toString() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}