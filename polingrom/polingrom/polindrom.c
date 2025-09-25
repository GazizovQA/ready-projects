#include <stdio.h>

#include <locale.h>
#include <conio.h>
#include <windows.h>


// ������� ��������, �������� �� ������ �����������
int isPalindrome(const char* str, int start, int end) {
    while (start <= end) {
        if (str[start++] != str[end--]) {
            return 0; // �� ���������
        }
    }
    return 1; // ���������
}

// ����� ������ �������� ����������
void findLongestPalindrome(char* str) {
    int maxLength = 0;
    int start = 0;
    int length = strlen(str); // ���������� ������� strlen ��� ����������� ����� ������

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
        printf("\n��������� �� ���������!\n");
    }
    else
    {
        // ����� ����������
        printf("����� ������� ���������: ");
        for (int i = start; i < start + maxLength; ++i) {
            putchar(str[i]);
        }
        printf("\n����� ����������: %d\n", maxLength);
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
        printf("����������� �������� ���� ���� ��������� (�����/����) ��� ���������\n������� Enter ��� ������������� ��������\n\n");
        printf("1. ���� ������ %s\n", choice == 0 ? "<---" : "");
        printf("   ��������� ������: [%s]\n", str); // ���������� ��������� ������ � �������
        printf("2. ���������� ������ �������� ����������� %s\n", choice == 1 ? "<---" : "");
        printf("3. ����� %s\n", choice == 2 ? "<---" : "");

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
        case 72: // ������� �����
            choice = (choice > 0) ? choice - 1 : 2;
            break;
        case 80: // ������� ����
            choice = (choice < 2) ? choice + 1 : 0;
            break;
        }
        if (key == 13) { // Enter
            switch (choice) {
            case 0:  
                system("cls");

                printf("������� ������: ");
                fgets(str, sizeof(str), stdin);

                // ������� ������ ����� ������, ���� �� ������������
                str[strcspn(str, "\n")] = '\0'; 
                break;
            case 1: findLongestPalindrome(str); break;
            case 2: return 0; 
            }
            printf("������� ����� �������, ����� ����������...");
            _getch();
        }
    }
    return 0;
}
