#include "11.1.h"

FILE* openFile(const char* fileName, const char* mode) {
    FILE* file;
    fopen_s(&file, fileName, mode);
    return file;
}

bool fileSuccessfullyOpened(FILE* file) {
    return file != nullptr;
}

void printErrorMessage(const char* operation) {
    perror(operation);
}

void closeFile(FILE* file) {
    if (file != nullptr) {
        fclose(file);
    }
}

bool checkFile(FILE* file, const char* error) {
    if (!fileSuccessfullyOpened(file)) {
        printErrorMessage(error);
        return false;
    }
    return true;
}

bool openAndCheckFile(FILE*& file, const char* fileName, const char* mode, const char* error) {
    file = openFile(fileName, mode);
    return checkFile(file, error);
}

bool readLine(FILE* file, char* line, size_t size) {
    return fgets(line, size, file) != nullptr;
}

bool linesIdentical(const char* line1, const char* line2) {
    return strcmp(line1, line2) == 0;
}

void compareFilesLineByLine(FILE* file1, FILE* file2) {
    char line1[256], line2[256];
    int lineNumber = 1;

    while (readLine(file1, line1, sizeof(line1)) && readLine(file2, line2, sizeof(line2))) {
        if (!linesIdentical(line1, line2)) {
            cout << "Строка " << lineNumber << " не совпадает " << endl;
            cout << "Файл1: " << line1;
            cout << "Файл2: " << line2;
        }
        lineNumber++;
    }
}

int countCharacters(FILE* file) {
    fseek(file, 0, SEEK_SET);
    int charCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != nullptr) {
        for (int i = 0; line[i] != '\0'; i++) {
            charCount++;
        }
    }
    return charCount;
}

int countLines(FILE* file) {
    fseek(file, 0, SEEK_SET);
    int lineCount = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != nullptr) {
        lineCount++;
    }
    return lineCount;
}

int countCharactersFromCharSet(FILE* file, const char* charSet) {
    fseek(file, 0, SEEK_SET);
    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != nullptr) {
        for (int i = 0; line[i] != '\0'; i++) {
            for (int j = 0; charSet[j] != '\0'; j++) {
                if (line[i] == charSet[j]) {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}

void printFileContents(FILE* file) {
    fseek(file, 0, SEEK_SET);
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        cout << line;
    }
}

void writeStatisticsToFile(FILE* file, int charCount, int lineCount, int vowelCount, int consonantCount, int digitCount) {
    fprintf(file, "Количество символов в первом файле: %d\n", charCount);
    fprintf(file, "Количество строк в первом файле: %d\n", lineCount);
    fprintf(file, "Количество гласных в первом файле: %d\n", vowelCount);
    fprintf(file, "Количество согласных в первом файле: %d\n", consonantCount);
    fprintf(file, "Количество цифр в первом файле: %d\n", digitCount);
    fflush(file);
}

void shiftLetters(char& symbol, int shift, bool left, const char* alphabet) {
    const char* foundSymbol = strchr(alphabet, symbol);
    if (foundSymbol) {
        int index = foundSymbol - alphabet;
        int length = strlen(alphabet) / 2; // Length of one half of the alphabet (26 letters)
        if (left) {
            symbol = alphabet[(index - shift + length) % length + (index >= length ? length : 0)];
        }
        else {
            symbol = alphabet[(index + shift) % length + (index >= length ? length : 0)];
        }
    }
}

void rewriteTextWithShift(FILE* inputFile, FILE* outputFile, int shift, bool left, const char* alphabet) {
    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        for (int i = 0; line[i] != '\0'; i++) {
            shiftLetters(line[i], shift, left, alphabet);
        }
        fputs(line, outputFile);
    }
}
