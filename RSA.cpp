#include "RSA.hpp"

#include <cmath>
#include <iostream>

namespace {
const int kE = 53;
const int kN = 299;
const int kP = 13;
const int kQ = 23;
const int kEilerFunc = 264;
const int kCryptedValue = 171;

int Gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int FindFirstCoprime(int n) {
    for (int a = 2; a < n; ++a) {
        if (Gcd(a, n) == 1) {
            return a;
        }
    }
    return -1;
}

long long unsigned int PowerModule(unsigned long long int base, int exp, int mod) {
    long long unsigned int result = 1;
    long long unsigned int baseMod = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * baseMod) % mod;
        }
        baseMod = (baseMod * baseMod) % mod;
        exp /= 2;
    }
    return result;
}

int CalculateD(int eilerFunc, int e) {
    int d{};
    while (true) {
        ++d;
        if ((e * d) % eilerFunc == 1) {
            return d;
        }
    }
}

void PrintResults(int e, int d, int n, unsigned long long int decryptedValue, unsigned long long int encryptedValue) {
    std::cout << "Зашифрованное значение: " << encryptedValue << '\n'
              << "Открытый ключ: {" << e << ',' << n << "}\n"
              << "Закрытый ключ: {" << d << ',' << n << "}\n"
              << "Расшифрованное значение: " << decryptedValue << std::endl;
}

}  // namespace

namespace RSA {
unsigned long long int Decrypt(int d, int n, unsigned long long int encryptedValue) {
    unsigned long long int decryptedValue = PowerModule(encryptedValue, d, n);
    return decryptedValue;
}

unsigned long long int Encrypt(int e, int n, int value) {
    unsigned long long int encryptedValue = PowerModule(value, e, n);
    return encryptedValue;
}

void StartMainTask() {
    int d = CalculateD(kEilerFunc, kE);
    unsigned long long int decryptedValue = Decrypt(d, kN, kCryptedValue);
    PrintResults(kE, d, kN, decryptedValue, kCryptedValue);
}

void StartEncryptDecryptAlgorithm() {
    std::cout << "Введите простые числа p и q через пробел" << '\n';
    int p{};
    int q{};
    std::cin >> p >> q;

    std::cout << "Введите число, которое хотите зашифровать" << '\n';
    int value{};
    std::cin >> value;

    int n = p * q;
    int eilerFunc = (p - 1) * (q - 1);
    int e = FindFirstCoprime(eilerFunc);
    int d = CalculateD(eilerFunc, e);
    unsigned long long int encryptedValue = Encrypt(e, n, value);
    unsigned long long int decryptedValue = Decrypt(d, n, encryptedValue);
    PrintResults(e, d, n, decryptedValue, encryptedValue);
}

void StartProgram() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        std::cout << "Введите, что вы хотите сделать!" << '\n' << "1: Выполнить ДЗ" << '\n' << "2: Зашифровать число" << std::endl;
        int a{};
        std::cin >> a;
        switch (a) {
            case 1:
                StartMainTask();
                break;
            case 2:
                StartEncryptDecryptAlgorithm();
                break;
            default:
                std::cout << "Введено невалидное значение!" << std::endl;
                break;
        }
        std::cout << "Вы хотите продолжить?(y/n)" << std::endl;
        std::cin >> continueExecution;
    }
}
}  // namespace RSA
