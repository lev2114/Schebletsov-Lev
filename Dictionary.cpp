#include "Dictionary.hpp"

#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const int kStartWordsNumber = 10;
const int kDictionaryAmplifier = 2;
const int kBinarySearchDivider = 2;

void ResizeDictionary(Dictionary::Dictionary*& dictionary, int& currentDictionarySize) {
    Dictionary::Dictionary* newDictionary = new Dictionary::Dictionary[currentDictionarySize * kDictionaryAmplifier];
    for (int i = 0; i < currentDictionarySize; ++i) {
        newDictionary[i] = dictionary[i];
    }
    delete[] dictionary;
    dictionary = newDictionary;

    currentDictionarySize *= kDictionaryAmplifier;
}

void SortDictionary(Dictionary::Dictionary*& dictionary, int& currentWordsNumber) {
    for (int i = 0; i < currentWordsNumber - 1; ++i) {
        for (int j = 0; j < currentWordsNumber - i - 1; ++j) {
            if (std::strcmp(dictionary[j].englishWord, dictionary[j + 1].englishWord) > 0) {
                Dictionary::Dictionary temp = dictionary[j];
                dictionary[j] = dictionary[j + 1];
                dictionary[j + 1] = temp;
            }
        }
    }
}

[[nodiscard]] int ReadOption() {
    std::cout << "Пожалуйста, скажите, что вы хотите сделать:\n1) Добавить слово в словарь\n2) удалить слово из словаря\n3) Перевести английское "
                 "слово на русский\n4) Перевести русское слово на английский\n5) Просмотр словаря\n6) Вывод словаря в файл\n7) Выход"
              << std::endl;
    int option{};
    std::cin >> option;
    return option;
}

void RequestWords(char*& russianWord, char*& englishWord) {
    std::cout << "Введите русское слово и английское слово через пробел!" << std::endl;
    std::cin >> russianWord >> englishWord;
}

void RequestEnglishWord(char*& englishWord) {
    std::cout << "Введите английское слово!" << std::endl;
    std::cin >> englishWord;
}

void RequestRussianWord(char*& russianWord) {
    std::cout << "Введите русское слово!" << std::endl;
    std::cin >> russianWord;
}

}  // namespace

namespace Dictionary {
[[nodiscard]] bool CraftBaseDictionary(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNumber) {
    std::ifstream dictionaryFile("Dictionary.txt", std::ios::in);
    if (!dictionaryFile) {
        std::cout << "Ошибка: Не удалось открыть файл Dictionary.txt. Возможно он отсутствует в папке" << std::endl;
        return false;
    }

    char* englishWord = new char[kStandardEnglishWordLen];
    char* russianWord = new char[kStandardRussianWordLen];

    while (dictionaryFile >> russianWord >> englishWord) {
        AddWord(dictionary, currentDictionarySize, currentWordsNumber, russianWord, englishWord);
    }
    dictionaryFile.close();
    delete[] russianWord;
    delete[] englishWord;
    return true;
}

void AddWord(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNumber, char*& russianWord, char*& englishWord) {
    if (currentWordsNumber == currentDictionarySize) {
        ResizeDictionary(dictionary, currentDictionarySize);
    }
    for (int i = 0; i < currentWordsNumber; ++i) {
        if (std::strcmp(englishWord, dictionary[i].englishWord) == 0) {
            std::cout << "Слово уже есть в словаре!" << std::endl;
            return;
        }
    }

    dictionary[currentWordsNumber].englishWord = new char[kStandardEnglishWordLen];
    dictionary[currentWordsNumber].russianWord = new char[kStandardRussianWordLen];

    std::strncpy(dictionary[currentWordsNumber].englishWord, englishWord, kStandardEnglishWordLen);
    std::strncpy(dictionary[currentWordsNumber].russianWord, russianWord, kStandardRussianWordLen);
    ++currentWordsNumber;
}

void DeleteWord(Dictionary*& dictionary, int& currentWordsNumber, char*& englishWord) {
    for (int i = 0; i < currentWordsNumber; ++i) {
        if (std::strcmp(englishWord, dictionary[i].englishWord) == 0) {
            delete[] dictionary[i].englishWord;
            delete[] dictionary[i].russianWord;
            for (int j = i; j < currentWordsNumber - 1; ++j) {
                dictionary[j] = dictionary[j + 1];
            }
            --currentWordsNumber;
            std::cout << "Слово удалено!" << std::endl;
            return;
        }
    }
    std::cout << "Такого слова нет!" << std::endl;
}

void TranslateWordToRussian(Dictionary*& dictionary, int& currentWordsNumber, char*& targetWord) {
    int left{};
    int right = currentWordsNumber - 1;

    while (left <= right) {
        int middle = left + (right - left) / kBinarySearchDivider;
        int cmp = std::strcmp(dictionary[middle].englishWord, targetWord);

        if (cmp == 0) {
            std::cout << "Перевод: " << dictionary[middle].russianWord << std::endl;
            return;
        } else if (cmp < 0) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    std::cout << "Такого слова нет!" << std::endl;
}

void TranslateWordToEnglish(Dictionary*& dictionary, int& currentWordsNumber, char*& russianWord) {
    for (int i = 0; i < currentWordsNumber; ++i) {
        if (std::strcmp(russianWord, dictionary[i].russianWord) == 0) {
            std::cout << "Перевод: " << dictionary[i].englishWord << std::endl;
            return;
        }
    }
    std::cout << "Такого слова нет!" << std::endl;
}

void PrintDictionary(Dictionary*& dictionary, int& currentWordsCount) {
    for (int i = 0; i < currentWordsCount; ++i) {
        std::cout << i + 1 << ": " << dictionary[i].russianWord << "  " << dictionary[i].englishWord << std::endl;
    }
}

void OutputToFile(Dictionary*& dictionary, int& currentWordsNumber) {
    std::ofstream dictionaryFile("Dictionary.txt", std::ios::out | std::ios::trunc);
    for (int i = 0; i < currentWordsNumber; ++i) {
        dictionaryFile << dictionary[i].russianWord << " " << dictionary[i].englishWord << std::endl;
    }
    dictionaryFile.close();
}

void OpenMenu(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNumber, char& continueExecution) {
    SortDictionary(dictionary, currentWordsNumber);
    int option = ReadOption();
    switch (static_cast<MenuOptions>(option)) {
        case MenuOptions::addWord: {
            char* russianWord = new char[kStandardRussianWordLen];
            char* englishWord = new char[kStandardEnglishWordLen];
            RequestWords(russianWord, englishWord);
            AddWord(dictionary, currentDictionarySize, currentWordsNumber, russianWord, englishWord);
            delete[] russianWord;
            delete[] englishWord;
            break;
        }
        case MenuOptions::deleteWord: {
            if (currentWordsNumber == 0) {
                std::cout << "В словаре не осталось слов!" << std::endl;
                break;
            }
            char* englishWord = new char[kStandardEnglishWordLen];
            RequestEnglishWord(englishWord);
            DeleteWord(dictionary, currentWordsNumber, englishWord);
            delete[] englishWord;
            break;
        }
        case MenuOptions::translateToRussian: {
            char* englishWord = new char[kStandardEnglishWordLen];
            RequestEnglishWord(englishWord);
            TranslateWordToRussian(dictionary, currentWordsNumber, englishWord);
            delete[] englishWord;
            break;
        }
        case MenuOptions::translateToEnglish: {
            char* russianWord = new char[kStandardRussianWordLen];
            RequestRussianWord(russianWord);
            TranslateWordToEnglish(dictionary, currentWordsNumber, russianWord);
            delete[] russianWord;
            break;
        }
        case MenuOptions::printDictionary: {
            PrintDictionary(dictionary, currentWordsNumber);
            break;
        }
        case MenuOptions::outputToFile:
            OutputToFile(dictionary, currentWordsNumber);
            break;
        default:
            continueExecution = 'n';
            break;
    }
}

void StartProgram() {
    char continueExecution = 'y';
    Dictionary* dictionary = new Dictionary[kStartWordsNumber];
    int currentDictionarySize = kStartWordsNumber;
    int currentWordsNumber{};
    bool isDictionaryCrafted = CraftBaseDictionary(dictionary, currentDictionarySize, currentWordsNumber);
    if (isDictionaryCrafted == false || currentWordsNumber == 0) {
        std::cout << "Словарь будет пустым!" << std::endl;
    }
    while (continueExecution == 'y') {
        OpenMenu(dictionary, currentDictionarySize, currentWordsNumber, continueExecution);
    }
    for (int i = 0; i < currentWordsNumber; ++i) {
        delete[] dictionary[i].englishWord;
        delete[] dictionary[i].russianWord;
    }
    delete[] dictionary;
}

}  // namespace Dictionary
