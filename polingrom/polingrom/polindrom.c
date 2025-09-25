#include <stdio.h>

#include <locale.h>
#include <conio.h>
#include <windows.h>


// Функция проверки, является ли строка палиндромом
int isPalindrome(const char* str, int start, int end) {
    while (start <= end) {
        if (str[start++] != str[end--]) {
            return 0; // Не палиндром
        }
    }
    return 1; // Палиндром
}

// Поиск самого длинного палиндрома
void findLongestPalindrome(char* str) {
    int maxLength = 0;
    int start = 0;
    int length = strlen(str); // Используем функцию strlen для определения длины строки

    for (int i = 0; i < length; ++i) {
        for (int j = i; j < length; ++j) {
            if (isPalindrome(str, i, j)) {
                int currentLength = j - i + 1;
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                    start = i;
                }
            }
        }
    }

    if (maxLength<2) {
        printf("\nПалиндром не обнаружен!\n");
    }
    else
    {
        // Вывод результата
        printf("Самый длинный палиндром: ");
        for (int i = start; i < start + maxLength; ++i) {
            putchar(str[i]);
        }
        printf("\nДлина палиндрома: %d\n", maxLength);
    }

   
}

int main() {
    setlocale(LC_ALL, "Rus");

    char choice = 0;
    char key;
    char str[1000];
    for (int i = 0; i < 1000; i++) str[i] = '\0';

    while (1)
    {
        system("cls");
        printf("Используйте цифровой блок либо стрелочки (вверх/вниз) для навигации\nНажмите Enter для подтверждения операции\n\n");
        printf("1. Ввод строки %s\n", choice == 0 ? "<---" : "");
        printf("   Введенная строка: [%s]\n", str); // Отображаем введенную строку в скобках
        printf("2. Нахождение самого длинного палиндромма %s\n", choice == 1 ? "<---" : "");
        printf("3. Выход %s\n", choice == 2 ? "<---" : "");

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
        case 72: // Стрелка вверх
            choice = (choice > 0) ? choice - 1 : 2;
            break;
        case 80: // Стрелка вниз
            choice = (choice < 2) ? choice + 1 : 0;
            break;
        }
        if (key == 13) { // Enter
            switch (choice) {
            case 0:  
                system("cls");

                printf("Введите строку: ");
                fgets(str, sizeof(str), stdin);

                // Удаляем символ новой строки, если он присутствует
                str[strcspn(str, "\n")] = '\0'; 
                break;
            case 1: findLongestPalindrome(str); break;
            case 2: return 0; 
            }
            printf("Нажмите любую клавишу, чтобы продолжить...");
            _getch();
        }
    }
    return 0;
}
