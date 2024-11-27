#include "Crypter.hpp"

#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const int kArrayAmplify = 2;
const int kMaxCharNumber = 256;
const int kStandartCodesLen = 100;
const int kStandartBufferLen = 2048;
const int kFilesNumber = 5;

int* ResizeIntArray(int* array, int& masLen) {
    int newLen = masLen * kArrayAmplify;
    int* newArray = new int[newLen];

    for (int numberOfCodes = 0; numberOfCodes < masLen; ++numberOfCodes) {
        newArray[numberOfCodes] = array[numberOfCodes];
    }

    delete[] array;

    masLen = newLen;

    return newArray;
}

bool AddIfUnique(int*& array, int& arrayLen, int value) {
    for (int i = 0; i < arrayLen; ++i) {
        if (array[i] == value) {
            return false;
        }
    }

    int* newArray = new int[arrayLen + 1];
    for (int i = 0; i < arrayLen; ++i) {
        newArray[i] = array[i];
    }
    newArray[arrayLen] = value;

    delete[] array;
    array = newArray;
    ++arrayLen;

    return true;
}

bool ContainsChar(char* symbols, int length, char target) {
    for (int i = 0; i < length; ++i) {
        if (symbols[i] == target) {
            return true;
        }
    }
    return false;
}

bool ContainsInt(int* array, int length, int target) {
    for (int i = 0; i < length; ++i) {
        if (array[i] == target) {
            return true;
        }
    }
    return false;
}

bool CheckFiles(const char* inputFile, const char* codebookFile, const char* encodedFile, const char* decodedFile) {
    std::ifstream input(inputFile);
    if (!input.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл " << inputFile << std::endl;
        return false;
    }
    input.close();

    std::ifstream codebook(codebookFile);
    if (!codebook.is_open()) {
        std::cout << "Ошибка: Не удалось открыть файл " << codebookFile << std::endl;
        return false;
    }
    codebook.close();

    std::ofstream encoded(encodedFile, std::ios::trunc);
    if (!encoded.is_open()) {
        std::cout << "Ошибка: Не удалось создать файл " << encodedFile << std::endl;
        return false;
    }
    encoded.close();

    std::ofstream decoded(decodedFile, std::ios::trunc);
    if (!decoded.is_open()) {
        std::cout << "Ошибка: Не удалось создать файл " << decodedFile << std::endl;
        return false;
    }
    decoded.close();
    return true;
}

void Encode(const char* inputFile, int* codes, const char* encodedFile, int& numberOfCodes, Crypter::Data& data) {
    std::ifstream input(inputFile, std::ios::binary | std::ios::in);
    std::ofstream encoded(encodedFile, std::ios::binary | std::ios::out);
    char symbol{};
    int i{};
    int charCount{};

    data.symbols = new char[kMaxCharNumber];
    data.symbolData = new Crypter::SymbolData[kMaxCharNumber];

    while (input.get(symbol)) {
        if (i == numberOfCodes) {
            i -= numberOfCodes;
        }
        if (!ContainsChar(data.symbols, kMaxCharNumber, symbol)){
            data.symbols[charCount] = symbol;
            data.codes[charCount] = static_cast<int>(symbol);
            data.symbolData[charCount].usageNumber = 0;
            charCount += 1;
        }

        int index = 0;
        while (data.symbols[index] != symbol) {
            ++index;
        }

        char encodedSymbol = symbol + static_cast<char>(codes[i]);  // NOLINT
        encoded.put(encodedSymbol);

        data.symbolData[index].usageNumber += 1;
        AddIfUnique(data.symbolData[index].differentCrypts, data.symbolData[index].usageNumber, encodedSymbol);

        ++i;
    }
    input.close();
    encoded.close();
}

void Decode(const char* encodedFile, const char* decodedFile, int* codes, int& numberOfCodes) {
    std::ifstream encoded(encodedFile, std::ios::binary | std::ios::in);
    std::ofstream decoded(decodedFile, std::ios::binary | std::ios::trunc | std::ios::out);

    char encodedSymbol{};
    int i{};
    while (encoded.get(encodedSymbol)) {
        if (i == numberOfCodes) {
            i -= numberOfCodes;
        }

        char symbol = encodedSymbol - static_cast<char>(codes[i]);  // NOLINT
        decoded.put(symbol);
        ++i;
    }

    encoded.close();
    decoded.close();
}

int* GetCodes(const char* codebookFile, int& numberOfCodes) {
    std::ifstream codebook(codebookFile, std::ios::binary | std::ios::in);
    char buffer[kStandartBufferLen];
    int* codes = new int[kStandartCodesLen]{};
    int codesLen = kStandartCodesLen;
    const char* delimiters = " .,!?;:\"'()-[]{}<>@#$/\\&*_+=%^";

    while (codebook.getline(buffer, kStandartBufferLen) || codebook.gcount() == kStandartBufferLen - 1) {
        if (codebook.fail() && !codebook.eof()) {
            codebook.clear();
        }

        char* word = strtok(buffer, delimiters);
        while (word != nullptr) {
            char sum = 0;
            for (int i = 0; word[i] != '\0'; ++i) {
                sum += word[i];  // NOLINT
            }

            if (numberOfCodes >= codesLen) {
                codes = ResizeIntArray(codes, codesLen);
            }

            codes[numberOfCodes] = static_cast<int>(sum);
            ++numberOfCodes;

            word = strtok(nullptr, delimiters);
        }
    }
    codebook.close();
    return codes;
}
}  // namespace

namespace Crypter {
void StartProgram(int argc, char** argv) {
    if (argc != kFilesNumber) {
        std::cerr << "Введено недостаточно аргументов командной строки!" << std::endl;
        return;
    }
    const char* inputFile = argv[1];
    const char* codebookFile = argv[2];
    const char* encodedFile = argv[3];
    const char* decodedFile = argv[4];

    if (!CheckFiles(inputFile, codebookFile, encodedFile, decodedFile)) {
        return;
    }

    int numberOfCodes{};

    Data data{};

    int* codes = GetCodes(codebookFile, numberOfCodes);

    data.wordsCount = numberOfCodes;

    Encode(inputFile, codes, encodedFile, numberOfCodes, data);

    Decode(encodedFile, decodedFile, codes, numberOfCodes);

    delete[] codes;
    delete[] data.symbols;
    delete[] data.symbolData;
}

}  // namespace Crypter
