#ifndef VIGENERE256ASCIICIPHER_H
#define VIGENERE256ASCIICIPHER_H

#include "Vigenere.h"

namespace Cipher { class Vigenere256ASCIICipher; }

class Vigenere256ASCIICipher : public VigenereCipher
{
public:
    Vigenere256ASCIICipher(std::string);

    void encrypt();
    void decrypt();
};

#endif // VIGENERE256ASCIICIPHER_H
