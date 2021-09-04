#include <include/cipher/vigenere/VigenereFull.h>

#include <algorithm>
#include <cstring>
#include <random>
#include <iostream>

const std::vector<char> VigenereFullCipher::ALPHABET({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'});

VigenereFullCipher::VigenereFullCipher(std::string key) : VigenereCipher(key)
{
    generateNewTable();
}

void VigenereFullCipher::setAlphabetArray(std::vector<std::vector<char>> table)
{
    alphabetArray = table;
}

std::vector<std::vector<char>> VigenereFullCipher::getAlphabetArray()
{
    return alphabetArray;
}

void VigenereFullCipher::setKey(std::string key)
{
    this->key = key;
}

std::string VigenereFullCipher::getKey()
{
    return key;
}

void VigenereFullCipher::encrypt()
{
    int repeatedKeyTimes = plainText.length() / key.length();

    std::string trueKey = key;
    for (int i = 0; i < repeatedKeyTimes; i++) {
        trueKey += key;
    }

    trueKey = trueKey.substr(0, plainText.length());

    cipherText = plainText;
    for (int i = 0; i < cipherText.length(); i++) {
        cipherText[i] = alphabetArray[trueKey[i] - CHAR_OFFSET][plainText[i] - CHAR_OFFSET];
    }
}

void VigenereFullCipher::decrypt()
{
    std::cout << cipherText << std::endl;
    std::cout << key << std::endl;
    int repeatedKeyTimes = cipherText.length() / key.length();

    std::string trueKey = key;
    for (int i = 0; i < repeatedKeyTimes; i++) {
        trueKey += key;
    }

    trueKey = trueKey.substr(0, cipherText.length());

    plainText = cipherText;
    for (int i = 0; i < plainText.length(); i++) {
        int keyOffset = trueKey[i] - CHAR_OFFSET;

        int plainTextOffset = 0;
        for (plainTextOffset = 0; plainTextOffset < 26; plainTextOffset++) {
            if (alphabetArray[keyOffset][plainTextOffset] == cipherText[i]) {
                break;
            }
        }

        plainText[i] = (char) (plainTextOffset + CHAR_OFFSET);
    }
}

void VigenereFullCipher::generateNewTable()
{
    alphabetArray.clear();
    std::random_device rd;
    std::default_random_engine rng = std::default_random_engine(rd());


    for (int i = 0; i < 26; i++) {
        std::vector<char> temp(ALPHABET);
        std::shuffle(std::begin(temp), std::end(temp), rng);
        alphabetArray.push_back(temp);
    }
}
