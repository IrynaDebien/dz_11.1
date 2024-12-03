#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdio>
using namespace std;

FILE* openFile(const char* fileName, const char* mode);
bool fileSuccessfullyOpened(FILE* file);
void printErrorMessage(const char* operation);
void closeFile(FILE* file);
bool checkFile(FILE* file, const char* error);
bool openAndCheckFile(FILE*& file, const char* fileName, const char* mode, const char* error);
bool readLine(FILE* file, char* line, size_t size);
bool linesIdentical(const char* line1, const char* line2);
void compareFilesLineByLine(FILE* file1, FILE* file2);
int countCharacters(FILE* file);
int countLines(FILE* file);
int countCharactersFromCharSet(FILE* file, const char* charSet);
void printFileContents(FILE* file);
void writeStatisticsToFile(FILE* file, int charCount, int lineCount, int vowelCount, int consonantCount, int digitCount);
void shiftLetters(char& symbol, int shift, bool left, const char* alphabet);
void rewriteTextWithShift(FILE* inputFile, FILE* outputFile, int shift, bool left, const char* alphabet);
