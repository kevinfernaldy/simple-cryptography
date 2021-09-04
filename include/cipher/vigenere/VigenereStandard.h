#ifndef VIGENERESTANDARDCIPHER_H
#define VIGENERESTANDARDCIPHER_H

#include "Vigenere.h"

namespace Cipher { class VigenereStandardCipher; }

class VigenereStandardCipher : public VigenereCipher
{
public:
    VigenereStandardCipher(std::string);

    void encrypt();
    void decrypt();

    static const char CHAR_OFFSET = 0x41;
};

#endif // VIGENERESTANDARDCIPHER_H
