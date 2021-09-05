#ifndef AFFINECIPHER_H
#define AFFINECIPHER_H

#include <string>

namespace Cipher { class AffineCipher; }

class AffineCipher
{
public:
    AffineCipher(int, int);

    void encrypt();
    void decrypt();

    void setCipherText(std::string);
    void setPlainText(std::string);
    std::string getCipherText(bool);
    std::string getPlainText();

    int modularInverse(int, int);

private:
    int a;
    int b;
    std::string plainText;
    std::string cipherText;
};

#endif // AFFINECIPHER_H
