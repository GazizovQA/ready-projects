#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h> // Для atoi

#define MAX_SIZE 20 // Максимальный размер массива


void fillSpiral(int n, int m, int spiral[MAX_SIZE][MAX_SIZE]) {
    int left = 0, right = m - 1, top = 0, bottom = n - 1;
    int num = 1;
    while (left <= right && top <= bottom) {
        // Заполнение верхней строки 
        for (int i = left; i <= right; i++) {
            spiral[top][i] = num++;
        }
        top++;
        // Заполнение правого столбца 
        for (int i = top; i <= bottom; i++) {
            spiral[i][right] = num++;
        }
        right--;
        // Заполнение нижней строки 
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                spiral[bottom][i] = num++;
            }
            bottom--;
        }
        // Заполнение левого столбца 
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                spiral[i][left] = num++;
            }
            left++;
        }
    }
}

void printSpiral(int n, int m, int spiral[MAX_SIZE][MAX_SIZE]) {
    // Вывод спирального массива 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%03d ", spiral[i][j]);
        }
        printf("\n");
    }
}

void mirrorSpiral(int n, int m, int spiral[MAX_SIZE][MAX_SIZE]) {
    // Отзеркаливание спирали по вертикали 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m / 2; j++) {
            int temp = spiral[i][j];
            spiral[i][j] = spiral[i][m - 1 - j];
            spiral[i][m - 1 - j] = temp;
        }
    }
}

void rotateSpiral(int n, int m, int spiral[MAX_SIZE][MAX_SIZE]) {
    // Поворот спирали на 180 градусов 
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m; j++) {
            int temp = spiral[i][j];
            spiral[i][j] = spiral[n - 1 - i][m - 1 - j];
            spiral[n - 1 - i][m - 1 - j] = temp;
        }
    }
    if (n % 2 == 1) {
        for (int j = 0; j < m / 2; j++) {
            int temp = spiral[n / 2][j];
            spiral[n / 2][j] = spiral[n / 2][m - 1 - j];
            spiral[n / 2][m - 1 - j] = temp;
        }
    }
}

void mirrorAndRotateSpiral(int n, int m, int spiral[MAX_SIZE][MAX_SIZE]) {
    // Поворот спирали на 180 градусов 
    rotateSpiral(n, m, spiral);
    // Отзеркаливание 
    mirrorSpiral(n, m, spiral);
}

void numberA(long long* a) {
    char input[20];
    char* endptr;

    system("cls");

    printf("Введите целочисленное число A (в пределах от 3 до 20) : ");
    fgets(input, sizeof(input), stdin); // Считываем строку

    *a = strtoll(input, &endptr, 10); // Преобразуем строку в число

    // Проверяем, было ли введено корректное число
    if (endptr == input || *endptr != '\n') {
        *a = 0; // Сброс значения
        printf("Ошибка: Введите корректное число!\n");
        _getch(); // Ожидание нажатия клавиши 
    }
    else if (*a < 3 || *a > 20) {
        *a = 0; // Сброс значения
        printf("Ошибка: число должно быть в пределах от 3 до 20.\n");
        _getch(); // Ожидание нажатия клавиши 
    }
}

void numberB(long long* b) {
    char input[20];
    char* endptr;

    system("cls");

    printf("Введите целочисленное число B (в пределах от 3 до 20) : ");
    fgets(input, sizeof(input), stdin); // Считываем строку

    *b = strtoll(input, &endptr, 10); // Преобразуем строку в число

    // Проверяем, было ли введено корректное число
    if (endptr == input || *endptr != '\n') {
        *b = 0; // Сброс значения
        printf("Ошибка: Введите корректное число!\n");
        _getch(); // Ожидание нажатия клавиши 
    }
    else if (*b < 3 || *b > 20) {
        *b = 0; // Сброс значения
        printf("Ошибка: число должно быть в пределах от 3 до 20.\n");
        _getch(); // Ожидание нажатия клавиши 
    }
}

// Функция сохранения в файл
void saveSpiralToFile(int n, int m, int spiral[MAX_SIZE][MAX_SIZE], const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(file, "%03d ", spiral[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Спираль сохранена в файл '%s'.\n", filename);
}

// Функция подсчета суммы чисел в файле
int sumElementsInFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Не удалось открыть файл '%s'.\n", filename);
        return -1;
    }
    int sum = 0;
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Удаляем символ новой строки
        if (strlen(line) == 0) continue;
        char* token = strtok(line, " ");
        while (token != NULL) {
            sum += atoi(token); // Преобразуем строку в число и добавляем к сумме
            token = strtok(NULL, " ");
        }
    }
    fclose(file);
    return sum;
}

int main() {
    setlocale(LC_ALL, "Rus");
    long long n = 0, m = 0;
    int spiral[MAX_SIZE][MAX_SIZE];
    int currentMenuItem = 0;
    char key;

    while (n == 0 || m == 0) {
        numberA(&n);
        if (n != 0) {
            numberB(&m);
            if (m != 0) fillSpiral(n, m, spiral);
        }
    }

    while (1) {
        system("cls");
        printf("Меню:\n");
        const char* menuItems[] = {
            "Показать исходную спираль",
            "Отзеркалить исходную спираль",
            "Повернуть исходную спираль на 180 градусов",
            "Повернуть и отзеркалить исходную спираль",
            "Ввести новые размеры матрицы",
            "Сохранить спираль в файл",
            "Подсчитать сумму чисел из файла", // Изменено название пункта
            "Выход"
        };
        for (int i = 0; i < 8; i++) {
            if (i == currentMenuItem) printf("> %s <\n", menuItems[i]);
            else printf("  %s\n", menuItems[i]);
        }
        key = _getch();
        if (key == 72) { // Стрелка вверх
            currentMenuItem = (currentMenuItem - 1 + 8) % 8;
        }
        else if (key == 80) { // Стрелка вниз
            currentMenuItem = (currentMenuItem + 1) % 8;
        }
        else if (key == '\r') { // Enter
            switch (currentMenuItem) {
            case 0: // Показать исходную
                system("cls");
                printf("\nИсходная спираль:\n");
                fillSpiral(n, m, spiral);
                printSpiral(n, m, spiral);
                _getch();
                break;
            case 1: // Отзеркалить
                system("cls");
                fillSpiral(n, m, spiral);
                mirrorSpiral(n, m, spiral);
                printf("\nОтзеркаленная спираль:\n");
                printSpiral(n, m, spiral);
                _getch();
                break;
            case 2: // Повернуть 180
                system("cls");
                fillSpiral(n, m, spiral);
                rotateSpiral(n, m, spiral);
                printf("\nПовернутая спираль:\n");
                printSpiral(n, m, spiral);
                _getch();
                break;
            case 3: // Повернуть и отзеркалить
                system("cls");
                fillSpiral(n, m, spiral);
                mirrorAndRotateSpiral(n, m, spiral);
                printf("\nПовернутая и отзеркаленная спираль:\n");
                printSpiral(n, m, spiral);
                _getch();
                break;
            case 4: // Новые размеры
                n = 0; m = 0;
                while (n == 0 || m == 0) {
                    numberA(&n);
                    if (n != 0) {
                        numberB(&m);
                        if (m != 0) fillSpiral(n, m, spiral);
                    }
                }
                break;
            case 5: // Сохранить в файл
            {
                system("cls");
                char filename[] = "gg";
                saveSpiralToFile(n, m, spiral, filename);
                _getch();
                break;
            }
            case 6: // Подсчет суммы чисел
            {
                system("cls");
                char sumFilename[] = "gg";
                int sum = sumElementsInFile(sumFilename);
                if (sum != -1) {
                    printf("Сумма чисел: %d\n", sum);
                }
                _getch();
                break;
            }
            case 7: // Выход
                return 0;
            }
        }
        else if (key == 27) { // ESC
            return 0;
        }
    }
    return 0;
}