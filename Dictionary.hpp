#ifndef DICTIONARY
#define DICTIONARY
namespace {
const int kStandardRussianWordLen = 72;
const int kStandardEnglishWordLen = 46;
}  // namespace
namespace Dictionary {
struct Dictionary {
    char* englishWord = nullptr;
    char* russianWord = nullptr;
};

enum class MenuOptions {
    addWord = 1,
    deleteWord,
    translateToRussian,
    translateToEnglish,
    printDictionary,
    outputToFile,
};

void StartProgram();

void OpenMenu(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNumber, char& continueExecution);

void AddWord(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordsNumber, char*& russianWord, char*& englishWord);

void DeleteWord(Dictionary*& dictionary, int& currentWordsNumber, char*& englishWord);

void TranslateWordToRussian(Dictionary*& dictionary, int& currentWordsNumber, char*& englishWord);

void TranslateWordToEnglish(Dictionary*& dictionary, int& currentWordsNumber, char*& russianWord);

void PrintDictionary(Dictionary*& dictionary, int& currentWordsCount);

void OutputToFile(Dictionary*& dictionary, int& currentWordsNumber);

bool CraftBaseDictionary(Dictionary*& dictionary, int& currentDictionarySize, int& currentWordCount);
}  // namespace Dictionary

#endif
