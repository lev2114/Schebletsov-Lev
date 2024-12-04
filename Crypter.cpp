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

bool AddIfUnique(int*& array, int& uniqueCodesUsageNumber, int value) {
    if (uniqueCodesUsageNumber == 0) {
        array[uniqueCodesUsageNumber] = value;
        ++uniqueCodesUsageNumber;
        return true;
    }
    for (int i = 0; i < uniqueCodesUsageNumber; ++i) {
        if (array[i] == value) {
            return false;
        }
    }

    array[uniqueCodesUsageNumber] = value;
    ++uniqueCodesUsageNumber;

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

bool IsFilesExist(const char* inputFile, const char* codebookFile, const char* encodedFile, const char* decodedFile) {
    std::ifstream input(inputFile);
    if (!input) {
        std::cout << "Ошибка: Не удалось открыть файл " << inputFile << std::endl;
        return false;
    }
    input.close();

    std::ifstream codebook(codebookFile);
    if (!codebook) {
        std::cout << "Ошибка: Не удалось открыть файл " << codebookFile << std::endl;
        return false;
    }
    codebook.close();

    std::ofstream encoded(encodedFile, std::ios::trunc);
    if (!encoded) {
        std::cout << "Ошибка: Не удалось создать файл " << encodedFile << std::endl;
        return false;
    }
    encoded.close();

    std::ofstream decoded(decodedFile, std::ios::trunc);
    if (!decoded) {
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
    int symbolCount{};

    data.symbols = new char[kMaxCharNumber];
    data.symbolData = new Crypter::SymbolData[kMaxCharNumber];
    data.codes = new int[kStandartCodesLen];
    for (int i = 0; i < kMaxCharNumber; ++i) {
        data.symbolData[i].differentCrypts = new int[kMaxCharNumber];
    }

    while (input.get(symbol)) {
        if (!ContainsChar(data.symbols, kMaxCharNumber, symbol)) {
            data.symbols[symbolCount] = symbol;
            data.codes[symbolCount] = static_cast<int>(symbol);
            symbolCount += 1;
        }

        int index = 0;
        while (data.symbols[index] != symbol) {
            ++index;
        }

        if (i == numberOfCodes) {
            i -= numberOfCodes;
        }
        std::cout << "Шифруем символ " << symbol << '\n';
        char encodedSymbol = symbol + static_cast<char>(codes[i]);
        encoded.put(encodedSymbol);

        data.symbolData[index].usageNumber += 1;
        AddIfUnique(data.symbolData[index].differentCrypts, data.symbolData[index].uniqueCodesUsageNumber, codes[i]);
        data.textLen += 1;

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

        char symbol = encodedSymbol - static_cast<char>(codes[i]);
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
                sum += word[i];
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
void PrintData(Data& data) {
    std::cout << "Размер блокнота: " << data.wordsCount << " слов." << std::endl;
    std::cout << "Длина исходного текста: " << data.textLen << " символов." <<std::endl;
    for (int i = 0; i < kMaxCharNumber;) {
        for (int j = i; j < i + 5; ++j) {
            std::cout << "Символ: " << data.symbols[j] << std::endl << "Код: " << data.codes[j] << std::endl;
            std::cout << "Символ встретился " << data.symbolData[j].usageNumber << " раз." << std::endl;
            std::cout << "Различных шифрований: " << data.symbolData[j].uniqueCodesUsageNumber << std::endl;
        }
        char scroll{};
        std::cout << "Следующие 5 или предыдущие 5?(n/p). Чтобы выйти введите 'e'" << '\n';
        std::cin >> scroll;
        if (scroll == 'p'){
            i -= 5;
        } else if (scroll == 'n'){
            i += 5;
        } else{
            return;
        }
    }
}

void StartProgram(int argc, char** argv) {
    if (argc != kFilesNumber) {
        std::cerr << "Введено недостаточно аргументов командной строки!" << std::endl;
        return;
    }
    const char* inputFile = argv[1];
    const char* codebookFile = argv[2];
    const char* encodedFile = argv[3];
    const char* decodedFile = argv[4];

    if (!IsFilesExist(inputFile, codebookFile, encodedFile, decodedFile)) {
        return;
    }

    int numberOfCodes{};

    Data data{};

    int* codes = GetCodes(codebookFile, numberOfCodes);

    data.wordsCount = numberOfCodes;

    Encode(inputFile, codes, encodedFile, numberOfCodes, data);

    Decode(encodedFile, decodedFile, codes, numberOfCodes);

    PrintData(data);

    for (int i = 0; i < kMaxCharNumber; ++i) {
        delete[] data.symbolData[i].differentCrypts;
    }
    delete[] data.symbolData;
    delete[] codes;
    delete[] data.symbols;
    delete[] data.codes;
}

}  // namespace Crypter
