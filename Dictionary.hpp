#ifndef DICTIONARY
#define DICTIONARY

namespace Dictionary {
struct Dictionary{
    char* englishWord;
    char* russianWord;
};

enum class MenuOptions{
    addWord = 1,
    deleteWord,
    translateToRussian,
    translateToEnglish,
    printDictionary,
    outputToFile,
};

void StartProgram();

void OpenMenu(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNumber);

void AddWord();

void DeleteWord();

void TranslateWordToRussian();

void TranslateWordToEnglish();

void PrintDictionary();

void OutputToFile();
} // namespace Dictionary


#endif
