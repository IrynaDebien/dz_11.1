#include "11.1.h"

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char cyrillicAlphabet[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const char* originalFile = "file1.txt";
    const char* comparisonFile = "file2.txt";
    const char* outputFile = "file3.txt";
    const char* encryptedFile = "file4.txt";
    const char vowels[] = { 'а', 'е', 'ё', 'и', 'о', 'у', 'ы', 'э', 'ю', 'я', 'А', 'Е', 'Ё', 'И', 'О', 'У', 'Ы', 'Э', 'Ю', 'Я', '\0' };
    const char consonants[] = { 'б', 'в', 'г', 'д', 'ж', 'з', 'й', 'к', 'л', 'м', 'н', 'п', 'р', 'с', 'т', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'Б', 'В', 'Г', 'Д', 'Ж', 'З', 'Й', 'К', 'Л', 'М', 'Н', 'П', 'Р', 'С', 'Т', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', '\0' };
    const char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0' };
    FILE* file1;
    FILE* file2;
    FILE* file3;
    FILE* file4;

    // задание1. Дано два текстовых файла. Выяснить, совпадают ли их строки. Если нет, то вывести на экран несовпадающие строки с обоих файлов.
    if (!openAndCheckFile(file1, originalFile, "r", "Ошибка при открытии первого файла")) {
        return 0;
    }
    if (!openAndCheckFile(file2, comparisonFile, "r", "Ошибка при открытии второго файла")) {
        closeFile(file1);
        return 0;
    }

    compareFilesLineByLine(file1, file2);
    fclose(file1);
    fclose(file2);

    // задание2. Дан текстовый файл. Необходимо создать новый файл и записать в него следующую статистику по исходному файлу:
    if (!openAndCheckFile(file1, originalFile, "r", "Ошибка при открытии исходного файла")) {
        return 0;
    }
    if (!openAndCheckFile(file3, outputFile, "w+", "Ошибка при открытии файла для записи")) {
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

    //задание 3 
    // Запрос у пользователя на шифр со здвигом
    int shift;
    char direction;
    cout << "Введите количество сдвига: ";
    cin >> shift;
    cout << "Введите направление (l - влево, r - вправо): ";
    cin >> direction;

    bool left = (direction == 'l');

    if (!openAndCheckFile(file2, originalFile, "r", "Ошибка при открытии исходного файла")) {
        return 0;
    }
    if (!openAndCheckFile(file4, encryptedFile, "w", "Ошибка при открытии шифрованого файла")) {
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
