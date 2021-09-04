#ifndef VIGENEREAUTOKEYCIPHER_H
#define VIGENEREAUTOKEYCIPHER_H

#include "Vigenere.h"

namespace Cipher { class VigenereAutoKeyCipher; }

class VigenereAutoKeyCipher : public VigenereCipher
{
public:
    VigenereAutoKeyCipher(std::string);

    void encrypt();
    void decrypt();

private:
    static const char CHAR_OFFSET = 0x41;
};

#endif // VIGENEREAUTOKEYCIPHER_H
