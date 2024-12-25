#include "Dictionary.hpp"

#include <cstring>
#include <iostream>
#include <fstream>

namespace {
const int kStartWordsNumber = 10;
const int kDictionaryAmplifier = 2;

void ResizeDictionary(Dictionary::Dictionary*& dictionary, int& currentDictionarySize){
    Dictionary::Dictionary* newDictionary = new Dictionary::Dictionary[currentDictionarySize*kDictionaryAmplifier];
    for (int i = 0; i < currentDictionarySize; ++i){
        newDictionary[i] = dictionary[i];
    }
    delete[] dictionary;
    dictionary = newDictionary;

    currentDictionarySize *= kDictionaryAmplifier;
}

[[nodiscard]] int ReadOption() {
    std::cout << "Пожалуйста, скажите, что вы хотите сделать:\n1) Добавить слово в словарь\n2) удалить слово из словаря\n3) Перевести английское "
                 "слово на русский\n4) Перевести русское слово на английский\n5) Просмотр словаря\n6) Вывод словаря в файл\n7) Выход"
              << std::endl;
    int option{};
    std::cin >> option;
    return option;
}

}  // namespace

namespace Dictionary {
void CraftBaseDictionary(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordCount){

}


void AddWord(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNuber){

}


void OpenMenu(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNumber, char& continueExecution) {
    int option = ReadOption();
    switch (static_cast<MenuOptions>(option)) {
        case MenuOptions::addWord:
            AddWord();
            break;
        case MenuOptions::deleteWord:
            DeleteWord();
            break;
        case MenuOptions::translateToRussian:
            TranslateWordToRussian();
            break;
        case MenuOptions::translateToEnglish:
            TranslateWordToEnglish();
            break;
        case MenuOptions::printDictionary:
            PrintDictionary();
            break;
        case MenuOptions::outputToFile:
            OutputToFile();
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
    int currentWordCount{};
    CraftBaseDictionary(dictionary, currentDictionarySize, currentWordCount);
    while(continueExecution == 'y'){
        OpenMenu(dictionary, currentDictionarySize, currentWordCount, continueExecution);
    }
    delete[] dictionary;
}

}  // namespace Dictionary
