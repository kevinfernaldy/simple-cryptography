#ifndef VIGENEREFULLCIPHER_H
#define VIGENEREFULLCIPHER_H

#include <vector>
#include "Vigenere.h"

namespace Cipher { class VigenereFullCipher; }

class VigenereFullCipher : public VigenereCipher
{
public:
    VigenereFullCipher(std::string);

    void encrypt();
    void decrypt();
    void generateNewTable();

    std::vector<std::vector<char>> getAlphabetArray();
    void setAlphabetArray(std::vector<std::vector<char>>);
    std::string getKey();
    void setKey(std::string);

private:
    static constexpr char CHAR_OFFSET = 0x41;
    static const std::vector<char> ALPHABET;

    std::vector<std::vector<char>> alphabetArray;
};

#endif // VIGENEREFULLCIPHER_H
