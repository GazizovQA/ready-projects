#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

const char* get_day_of_week(int day, int month, int year) {
    if (month < 3) {
        month += 12; 
        year -= 1;
    }
    int q = day;
    int m = month;
    int K = year % 100;
    int J = year / 100;
    int f = q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 - 2 * J;
    int day_of_week = f % 7;
    const char* days[] = { "Суббота", "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница" };
    return days[day_of_week];
}

int input_date(char* input) {
    int i = 0;
    char ch;
    while (i < 10) { 
        ch = _getch(); 
        if (ch == 8 && i > 0) { 
            i--;
            printf("\b \b");
            if (i == 2 || i == 5) {
                i--;
                printf("\b \b");
            }
            continue;
        }
        if (ch >= '0' && ch <= '9') {
            input[i] = ch;
            i++;
            putchar(ch);
        }
        if (i == 2 || i == 5) {
            input[i] = '.';
            i++;
            putchar('.');
        }
    }
    input[i] = '\0'; 
    return i; 
}

int input_time(char* input) {
    int i = 0;
    char ch;
    while (i < 8) { 
        ch = _getch(); 
        if (ch == 8 && i > 0) { 
            i--;
            printf("\b \b");
            if (i == 2 || i == 5) {
                i--;
                printf("\b \b");
            }
            continue;
        }
        if (ch >= '0' && ch <= '9') {
            input[i] = ch;
            i++;
            putchar(ch);
        }
        if (i == 2 || i == 5) {
            input[i] = ':';
            i++;
            putchar(':');
        }
    }
    input[i] = '\0'; 
    return i; 
}

// Функция для проверки високосного года
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Функция для получения количества дней в месяце
int days_in_month(int month, int year) {
    int days[] = { 31, 28 + is_leap_year(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return days[month - 1];
}

void calculate_difference(int day1, int month1, int year1, int hour1, int minute1, int second1,
    int day2, int month2, int year2, int hour2, int minute2, int second2) {
    // Приводим обе даты к количеству дней с начала эпохи
    int total_days1 = year1 * 365 + (year1 / 4) - (year1 / 100) + (year1 / 400);
    for (int m = 1; m < month1; m++) {
        total_days1 += days_in_month(m, year1);
    }
    total_days1 += day1;

    int total_days2 = year2 * 365 + (year2 / 4) - (year2 / 100) + (year2 / 400);
    for (int m = 1; m < month2; m++) {
        total_days2 += days_in_month(m, year2);
    }
    total_days2 += day2;

    // Находим разницу в днях
    int day_difference = total_days2 - total_days1;

    // Преобразуем время в секунды
    int total_seconds1 = (hour1 * 3600) + (minute1 * 60) + second1;
    int total_seconds2 = (hour2 * 3600) + (minute2 * 60) + second2;

    // Общая разница в секундах
    int seconds_difference = total_seconds2 - total_seconds1;

    // Если разница в секундах отрицательная, уменьшаем дни и добавляем 86400 секунд
    if (seconds_difference < 0) {
        day_difference--;
        seconds_difference += 86400; // 24 * 3600
    }

    // Если day_difference отрицательная, это значит, что первая дата больше
    if (day_difference < 0) {
        // Инвертируем разницу
        day_difference = -day_difference;
        seconds_difference = -seconds_difference;

        // Если seconds_difference отрицательная, значит, нужно уменьшить день
        if (seconds_difference < 0) {
            day_difference--;
            seconds_difference += 86400; // 24 * 3600
        }
    }

    // Преобразуем разницу в годы, дни и время
    int years = day_difference / 365; // Примерно, не учитывает високосные годы
    day_difference -= years * 365; // Убираем полные годы
    int days = day_difference; // Остаток - количество дней

    int hours = seconds_difference / 3600;
    seconds_difference -= hours * 3600;
    int minutes = seconds_difference / 60;
    int seconds = seconds_difference % 60;

    printf("\nРазница: %d лет, %d дней, %d часов, %d минут, %d секунд.\n", years, days, hours, minutes, seconds);
}

int is_valid_date(int day, int month, int year) {
    if (year < 1930 || year > 2030) {
        return 0; // Неверный год
    }
    if (month < 1 || month > 12) {
        return 0; // Неверный месяц
    }
    int days_in_this_month = days_in_month(month, year);
    return (day >= 1 && day <= days_in_this_month); // Проверка на допустимый день
}

int is_valid_time(int hour, int minute, int second) {
    return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59) && (second >= 0 && second <= 59);
}

// Функция для добавления или вычитания дней из даты
void modify_date(int* day, int* month, int* year, int days) {
    int total_days = days;
    while (total_days != 0) {
        if (total_days > 0) {
            (*day)++;
            if (*day > days_in_month(*month, *year)) {
                (*day) = 1;
                (*month)++;
                if (*month > 12) {
                    (*month) = 1;
                    (*year)++;
                }
            }
            total_days--;
        }
        else {
            (*day)--;
            if (*day < 1) {
                (*month)--;
                if (*month < 1) {
                    (*month) = 12;
                    (*year)--;
                }
                (*day) = days_in_month(*month, *year);
            }
            total_days++;
        }
    }
}

void request_days_and_modify_date(char* date_input) {
    int days;
    printf("Введите количество дней от -10000 до 10000: ");
    if (scanf("%d", &days) != 1) {
        printf("\nОшибка: некорректный ввод. Пожалуйста, введите целое число.\n");
        while (getchar() != '\n'); // Очистка входного буфера
        return;
    }

    if (days < -10000 || days > 10000) {
        printf("\nОшибка: число дней должно быть в диапазоне от -10000 до 10000.\n");
        return;
    }

    int day, month, year;
    if (sscanf(date_input, "%d.%d.%d", &day, &month, &year) != 3) {
        printf("\nОшибка: не удалось распознать дату.\n");
        return;
    }

    modify_date(&day, &month, &year, days);
    printf("\nНовая дата: %02d.%02d.%04d\n", day, month, year);
}

void modify_time(int* hour, int* minute, int* second, int add_hour, int add_minute, int add_second) {
    *second += add_second;
    if (*second >= 60) {
        *minute += *second / 60;
        *second %= 60;
    }

    *minute += add_minute;
    if (*minute >= 60) {
        *hour += *minute / 60;
        *minute %= 60;
    }

    *hour += add_hour;
    if (*hour >= 24) {
        *hour %= 24;
    }
}

void request_time_and_modify(char* time_input) {
    int add_hour, add_minute, add_second;
    printf("Введите время для добавления (XX:XX:XX): ");
    char temp_time[9]; // Формат XX:XX:XX + null terminator
    input_time(temp_time);

    // Парсим введенное время
    if (sscanf(temp_time, "%d:%d:%d", &add_hour, &add_minute, &add_second) != 3) {
        printf("\nОшибка: некорректный ввод времени.\n");
        return;
    }

    // Проверяем корректность добавляемого времени
    if (!is_valid_time(add_hour, add_minute, add_second)) {
        printf("\nОшибка: недопустимое время для добавления.\n");
        return;
    }

    int hour, minute, second;
    if (sscanf(time_input, "%d:%d:%d", &hour, &minute, &second) != 3) {
        printf("\nОшибка: не удалось распознать текущее время.\n");
        return;
    }

    modify_time(&hour, &minute, &second, add_hour, add_minute, add_second);
    printf("\nРезультат: %02d:%02d:%02d\n", hour, minute, second);
}

int main() {
    setlocale(LC_ALL, "Rus");
    char input1[11]; // Формат XX.XX.XXXX + null terminator
    char input2[11]; 
    char time_input1[9]; // Формат XX:XX:XX + null terminator
    char time_input2[9]; 

    // Инициализация массивов нулями
    for (int i = 0; i < 11; i++) input1[i] = '\0';
    for (int i = 0; i < 11; i++) input2[i] = '\0';
    for (int i = 0; i < 9; i++) time_input1[i] = '\0';
    for (int i = 0; i < 9; i++) time_input2[i] = '\0';

    int choice = 0;
    char key;

    while (1) {
        system("cls");
        printf("Лабораторная <Календарь>\n\n");
        printf("Переключение по меню производится стрелочками (вверх вниз) и цифровым блоком(1-9).\n Выход осуществляется нажатием ESC, либо выбором соответствующего пункта меню.\n\n");
        printf("1) Ввод первой даты (%s) %s\n", input1[0] ? input1 : "", (choice == 0) ? "<---" : "");
        printf("2) Ввод первого времени (%s) %s\n", time_input1[0] ? time_input1 : "", (choice == 1) ? "<---" : "");
        printf("3) Ввод второй даты (%s) %s\n", input2[0] ? input2 : "", (choice == 2) ? "<---" : "");
        printf("4) Ввод второго времени (%s) %s\n", time_input2[0] ? time_input2 : "", (choice == 3) ? "<---" : "");
        printf("5) Вычислить разницу %s\n", (choice == 4) ? "<---" : "");
        printf("6) Изменить первую дату %s\n", (choice == 5) ? "<---" : "");
        printf("7) Изменить вторую дату %s\n", (choice == 6) ? "<---" : "");
        printf("8) Изменить первое время %s\n", (choice == 7) ? "<---" : "");
        printf("9) Изменить второе время %s\n", (choice == 8) ? "<---" : "");
        printf("\n0) Выход %s\n", (choice == 9) ? "<---" : "");
        key = _getch();

        switch (key) {
        case 27:
            printf("\nВыход из программы.\n");
            return 0;
        case 49: // '1'
            choice = 0;
            break;
        case 50: // '2'
            choice = 1;
            break;
        case 51: // '3'
            choice = 2;
            break;
        case 52: // '4'
            choice = 3;
            break;
        case 53: // '5'
            choice = 4;
            break;
        case 54: // '6'
            choice = 5;
            break;
        case 55: // '7'
            choice = 6;
            break;
        case 56: // '8'
            choice = 7;
            break;
        case 57: // '9'
            choice = 8;
            break;
        case 48: // '0'
            choice = 9;
            break;
        case 72: // Стрелка вверх
            choice = (choice > 0) ? choice - 1 : 9;
            break;
        case 80: // Стрелка вниз
            choice = (choice < 9) ? choice + 1 : 0;
            break;
        }

        if (key == 13) {
            switch (choice) {
            case 0:
                system("cls");
                printf("Введите первую дату в формате XX.XX.XXXX (Пожалуйста, укажите даты в пределах 1930-2030 годов.):\n");
                // Ввод первой даты
                if (input_date(input1) == 10) {
                    int day, month, year;
                    if (sscanf(input1, "%d.%d.%d", &day, &month, &year) != 3) {
                        printf("\nОшибка: не удалось распознать дату.\n");
                        for (int i = 0; i < 11; i++) input1[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    // Проверка на корректность даты
                    if (!is_valid_date(day, month, year)) {
                        printf("\nОшибка: недопустимая дата.\n");
                        for (int i = 0; i < 11; i++) input1[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    // Вычисление дня недели
                    const char* day_name = get_day_of_week(day, month, year);
                    printf("\nДень недели для первой даты: %s\n", day_name);
                }
                break;
            case 1:
                system("cls");
                printf("Введите первое время в формате XX:XX:XX (например, 14:13:23):\n");
                // Ввод первого времени
                if (input_time(time_input1) == 8) {
                    int hour, minute, second;
                    if (sscanf(time_input1, "%d:%d:%d", &hour, &minute, &second) != 3) {
                        printf("\nОшибка: не удалось распознать время.\n");
                        for (int i = 0; i < 9; i++) time_input1[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    // Проверка на корректность времени
                    if (!is_valid_time(hour, minute, second)) {
                        printf("\nОшибка: недопустимое время. Пожалуйста, введите время в формате от 00:00:00 до 23:59:59.\n");
                        for (int i = 0; i < 9; i++) time_input1[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    printf("\nВы ввели первое время: %s\n", time_input1);
                }
                break;
            case 2:
                system("cls");
                printf("Введите вторую дату в формате XX.XX.XXXX (Пожалуйста, укажите даты в пределах 1930-2030 годов.):\n");
                // Ввод второй даты
                if (input_date(input2) == 10) {
                    int day, month, year;
                    if (sscanf(input2, "%d.%d.%d", &day, &month, &year) != 3) {
                        printf("\nОшибка: не удалось распознать дату.\n");
                        for (int i = 0; i < 11; i++) input2[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    // Проверка на корректность даты
                    if (!is_valid_date(day, month, year)) {
                        printf("\nОшибка: недопустимая дата.\n");
                        for (int i = 0; i < 11; i++) input2[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    // Вычисление дня недели
                    const char* day_name = get_day_of_week(day, month, year);
                    printf("\nДень недели для второй даты: %s\n", day_name);
                }
                break;
            case 3:
                system("cls");
                printf("Введите второе время в формате XX:XX:XX (например, 14:13:23):\n");
                // Ввод второго времени
                if (input_time(time_input2) == 8) {
                    int hour, minute, second;
                    if (sscanf(time_input2, "%d:%d:%d", &hour, &minute, &second) != 3) {
                        printf("\nОшибка: не удалось распознать время.\n");
                        for (int i = 0; i < 9; i++) time_input2[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    // Проверка на корректность времени
                    if (!is_valid_time(hour, minute, second)) {
                        printf("\nОшибка: недопустимое время. Пожалуйста, введите время в формате от 00:00:00 до 23:59:59.\n");
                        for (int i = 0; i < 9; i++) time_input2[i] = '\0';
                        printf("Нажмите любую кнопку чтобы продолжить...");
                        _getch();
                        continue;
                    }
                    printf("\nВы ввели второе время: %s\n", time_input2);
                }
                break;
            case 4:
                // Вычисление разницы между датами и временем
                int day1, month1, year1, hour1, minute1, second1;
                int day2, month2, year2, hour2, minute2, second2;

                if (sscanf(input1, "%d.%d.%d", &day1, &month1, &year1) != 3 ||
                    sscanf(time_input1, "%d:%d:%d", &hour1, &minute1, &second1) != 3 ||
                    sscanf(input2, "%d.%d.%d", &day2, &month2, &year2) != 3 ||
                    sscanf(time_input2, "%d:%d:%d", &hour2, &minute2, &second2) != 3) {
                    printf("\nОшибка: не удалось распознать одну из дат или времени.\n");
                    printf("Нажмите любую кнопку чтобы продолжить...");
                    _getch();
                    continue;
                }

                if (!is_valid_date(day1, month1, year1) || !is_valid_date(day2, month2, year2)) {
                    printf("\nОшибка: одна из дат недопустима. Пожалуйста, проверьте ввод.\n");
                    printf("Нажмите любую кнопку чтобы продолжить...");
                    _getch();
                    continue;
                }

                if (!is_valid_time(hour1, minute1, second1) || !is_valid_time(hour2, minute2, second2)) {
                    printf("\nОшибка: одно из времен недопустимо. Пожалуйста, проверьте ввод.\n");
                    printf("Нажмите любую кнопку чтобы продолжить...");
                    _getch();
                    continue;
                }

                calculate_difference(day1, month1, year1, hour1, minute1, second1,
                    day2, month2, year2, hour2, minute2, second2);
                break;
            case 5:
                system("cls");
                request_days_and_modify_date(input1);
                break;
            case 6:
                system("cls");
                request_days_and_modify_date(input2);
                break;
            case 7:
                system("cls");
                request_time_and_modify(time_input1);
                break;
            case 8:
                system("cls");
                request_time_and_modify(time_input2);
                break;
            case 9:
                return 0;
            }
            
            printf("Нажмите любую кнопку чтобы продолжить...");
            _getch();
        }
    }
    return 0;
}