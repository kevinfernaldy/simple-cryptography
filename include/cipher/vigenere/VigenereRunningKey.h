#ifndef VIGENERERUNNINGKEY_H
#define VIGENERERUNNINGKEY_H

#include "Vigenere.h"

namespace Cipher { class VigenereRunningKeyCipher; }

class VigenereRunningKeyCipher : public VigenereCipher
{
public:
    VigenereRunningKeyCipher(std::string);

    void encrypt();
    void decrypt();

private:
    static const char CHAR_OFFSET = 0x41;
};

#endif // VIGENERERUNNINGKEY_H
