#include "11.1.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char cyrillicAlphabet[] = "�������������������������������������Ũ��������������������������";
    const char* originalFile = "file1.txt";
    const char* comparisonFile = "file2.txt";
    const char* outputFile = "file3.txt";
    const char* encryptedFile = "file4.txt";
    const char vowels[] = { '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '\0' };
    const char consonants[] = { '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '\0' };
    const char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' };
    FILE* file1;
    FILE* file2;
    FILE* file3;
    FILE* file4;

    // �������1. ���� ��� ��������� �����. ��������, ��������� �� �� ������. ���� ���, �� ������� �� ����� ������������� ������ � ����� ������.
    if (!openAndCheckFile(file1, originalFile, "r", "������ ��� �������� ������� �����")) {
        return 0;
    }
    if (!openAndCheckFile(file2, comparisonFile, "r", "������ ��� �������� ������� �����")) {
        closeFile(file1);
        return 0;
    }

    compareFilesLineByLine(file1, file2);
    fclose(file1);
    fclose(file2);

    // �������2. ��� ��������� ����. ���������� ������� ����� ���� � �������� � ���� ��������� ���������� �� ��������� �����:
    if (!openAndCheckFile(file1, originalFile, "r", "������ ��� �������� ��������� �����")) {
        return 0;
    }
    if (!openAndCheckFile(file3, outputFile, "w+", "������ ��� �������� ����� ��� ������")) {
        closeFile(file1);
        return 0;
    }

    int charCount = countCharacters(file1);
    int lineCount = countLines(file1);
    int vowelCount = countCharactersFromCharSet(file1, vowels);
    int consonantCount = countCharactersFromCharSet(file1, consonants);
    int digitCount = countCharactersFromCharSet(file1, digits);

    writeStatisticsToFile(file3, charCount, lineCount, vowelCount, consonantCount, digitCount);

    printFileContents(file3);
    fclose(file1);
    fclose(file3);

    //������� 3 
    // ������ � ������������ �� ���� �� �������
    int shift;
    char direction;
    cout << "������� ���������� ������: ";
    cin >> shift;
    cout << "������� ����������� (l - �����, r - ������): ";
    cin >> direction;

    bool left = (direction == 'l');

    if (!openAndCheckFile(file2, originalFile, "r", "������ ��� �������� ��������� �����")) {
        return 0;
    }
    if (!openAndCheckFile(file4, encryptedFile, "w", "������ ��� �������� ����������� �����")) {
        closeFile(file2);
        return 0;
    }

    rewriteTextWithShift(file2, file4, shift, left, cyrillicAlphabet);

    fclose(file2);
    fclose(file4);

    file4 = openFile(encryptedFile, "r");
    printFileContents(file4);
    closeFile(file4);

    return 0;
}
