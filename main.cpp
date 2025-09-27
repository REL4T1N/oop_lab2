#include <iostream>
#include "include/lab2.h"

void demonstrateOperations() {
    std::cout << "=== Demonstration of Eleven class ===\n\n";
    
    // Создание чисел
    Eleven num1("A3");
    Eleven num2("27");
    
    std::cout << "Number 1: " << num1.toString() << std::endl;
    std::cout << "Number 2: " << num2.toString() << std::endl;
    
    // Арифметические операции
    Eleven sum = num1.add(num2);
    Eleven diff = num1.subtract(num2);
    
    std::cout << "Sum: " << sum.toString() << std::endl;
    std::cout << "Difference: " << diff.toString() << std::endl;
    
    // Операции сравнения
    std::cout << "num1 > num2: " << (num1.greaterThan(num2) ? "true" : "false") << std::endl;
    std::cout << "num1 < num2: " << (num1.lessThan(num2) ? "true" : "false") << std::endl;
    std::cout << "num1 == num2: " << (num1.equals(num2) ? "true" : "false") << std::endl;
}

int main() {
    try {
        demonstrateOperations();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}