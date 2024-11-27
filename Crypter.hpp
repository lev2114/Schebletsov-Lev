#ifndef CRYPTER
#define CRYPTER

namespace Crypter {

struct SymbolData{
    int usageNumber{};
    int* differentCrypts = nullptr;
};

struct Data {
    char* symbols = nullptr;
    int* codes = nullptr;
    SymbolData* symbolData = nullptr;
    int wordsCount{};
    int textLen{};
};

void StartProgram(int argc, char** argv);
}  // namespace Crypter

#endif  // DEFINE CRYPTER
