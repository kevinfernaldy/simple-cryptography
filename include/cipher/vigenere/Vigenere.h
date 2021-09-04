#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <string>

namespace Cipher { class VigenereCipher; }

class VigenereCipher
{
public:
    VigenereCipher(std::string);

    virtual void encrypt() = 0;
    virtual void decrypt() = 0;

protected:
    std::string cipherText;
    std::string plainText;
    std::string key;
};

#endif // VIGENERECIPHER_H
