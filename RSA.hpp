#ifndef DZ
#define DZ

namespace RSA{
unsigned long long int Decrypt(int d, int n, unsigned long long int encryptedValue);
unsigned long long int Encrypt(int e, int n, int value);

void StartProgram();
void StartMainTask();
void StartEncryptDecryptAlgorithm();
}

#endif // DEFINE DZ
