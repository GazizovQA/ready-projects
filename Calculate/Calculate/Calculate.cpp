#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <locale.h>
#include <stdlib.h>


void numberA(long long* a) {

    char input[20]; 
    char* endptr;

    system("cls");
    
    printf("Введите целочисленное число A (в пределах -65536 - 65535) : ");
    fgets(input, sizeof(input), stdin); // Считываем строку

    *a = strtoll(input, &endptr, 10); // Преобразуем строку в число

    // Проверяем, было ли введено корректное число
    if (endptr == input || *endptr != '\n') {
       printf("Ошибка: Введите корректное число!\n");
        *a = 0; // Сброс значения
    }
    else if (*a < -65536 || *a > 65535) {
        printf("Ошибка: число должно быть в пределах -65536 - 65535.\n");
        *a = 0; // Сброс значения
    }
    
}

void numberB(long long* b) {

    char input[20];
    char* endptr;

    system("cls");

    printf("Введите целочисленное число B (в пределах -65536 - 65535) : ");
    fgets(input, sizeof(input), stdin); // Считываем строку

    *b = strtoll(input, &endptr, 10); // Преобразуем строку в число

    // Проверяем, было ли введено корректное число
    if (endptr == input || *endptr != '\n') {
        printf("Ошибка: Введите корректное число!\n");
        *b = 0; // Сброс значения
        }
    else if (*b < -65536 || *b > 65535) {
        printf("Ошибка: число должно быть в пределах -65536 - 65535.\n");
        *b = 0; // Сброс значения
    }
}

void add(long long a, long long b) {

    printf("Результат сложения: %lld + %lld = %lld\n", a, b, a + b);
}

void subtract(long long a, long long b) {

    printf("Результат вычитания: %lld - %lld = %lld\n", a, b, a - b);
}

void multiply(long long a, long long b) {

    printf("Результат умножения: %lld * %lld = %lld\n", a, b, a * b);
}

void divide(long long a, long long b) {

    if (b != 0) {
        printf("Результат деления: %lld // %lld = %lld\n", a, b, a / b);
    }
    else {
        printf("Ошибка: Деление на ноль!\n");
    }
}

int main() {

    char choice = 0;
    long long a = 0; 
    long long b = 0; 
    char key;

    setlocale(LC_ALL, "Rus");

    while (1) {
        system("cls");
        printf("Калькулятор\n\n");
        printf("Используйте цифровой блок либо стрелочки (вверх/вниз) для навигации\nНажмите Enter для подтверждения операции\n\n");
        printf("1. Введите число A (ваше число А: %lld) %s\n", a, choice == 0 ? "<---" : "");
        printf("2. Введите число B (ваше число В: %lld) %s\n", b, choice == 1 ? "<---" : "");
        printf("3. Сложение %s\n", choice == 2 ? "<---" : "");
        printf("4. Вычитание %s\n", choice == 3 ? "<---" : "");
        printf("5. Умножение %s\n", choice == 4 ? "<---" : "");
        printf("6. Деление %s\n", choice == 5 ? "<---" : "");
        printf("7. Выход %s\n", choice == 6 ? "<---" : "");

        key = _getch();

        switch (key) {
        case 27: // Esc
            return 0;
        case 49: // 1
            choice = 0;
            break;
        case 50: // 2
            choice = 1;
            break;
        case 51: // 3
            choice = 2;
            break;
        case 52: // 4
            choice = 3;
            break;
        case 53: // 5
            choice = 4;
            break;
        case 54: // 6
            choice = 5;
            break;
        case 55: // 7
            choice = 6;
            break;
        case 72: // Стрелка вверх
            choice = (choice > 0) ? choice - 1 : 6;
            break;
        case 80: // Стрелка вниз
            choice = (choice < 6) ? choice + 1 : 0;
            break;
        }

        if (key == 13) { // Enter
            switch (choice) {
            case 0: numberA(&a); break;
            case 1: numberB(&b); break;
            case 2: add(a, b); break;
            case 3: subtract(a, b); break;
            case 4: multiply(a, b); break;
            case 5: divide(a, b); break;
            case 6: return 0; // Выход
            }
            printf("Нажмите любую клавишу, чтобы продолжить...");
            _getch();
        }
    }
    return 0;
}