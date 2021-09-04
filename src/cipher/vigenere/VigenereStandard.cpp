#include "../../../include/cipher/vigenere/VigenereStandard.h"
#include <algorithm>
#include <sstream>

VigenereStandardCipher::VigenereStandardCipher(std::string key) : VigenereCipher(key)
{

}

void VigenereStandardCipher::setPlainText(std::string text)
{
    plainText = text;
}

void VigenereStandardCipher::setCipherText(std::string text)
{
    cipherText = text;
}

std::string VigenereStandardCipher::getPlainText()
{
    return plainText;
}

std::string VigenereStandardCipher::getCipherText(bool isSpaced)
{
    if (isSpaced) {
        std::ostringstream stream;
        stream << cipherText[0];
        for (int i = 1; i < cipherText.size(); i++) {
            if (i % 5 == 0) {
                stream << " ";
            }
            stream << cipherText[i];
        }

        return stream.str();

    } else {
        return cipherText;
    }
}

void VigenereStandardCipher::encrypt()
{
    int repeatedKeyTimes = plainText.length() / key.length();

    std::string trueKey = key;
    for (int i = 0; i < repeatedKeyTimes; i++) {
        trueKey += key;
    }

    trueKey = trueKey.substr(0, plainText.length());

    cipherText = plainText;
    for (int i = 0; i < cipherText.length(); i++) {
        cipherText[i] = (cipherText[i] + trueKey[i] - CHAR_OFFSET * 2) % 26 + CHAR_OFFSET;
    }
}

void VigenereStandardCipher::decrypt()
{
    int repeatedKeyTimes = cipherText.length() / key.length();

    std::string trueKey = key;
    for (int i = 0; i < repeatedKeyTimes; i++) {
        trueKey += key;
    }

    trueKey = trueKey.substr(0, cipherText.length());

    plainText = cipherText;
    for (int i = 0; i < plainText.length(); i++) {
        int temp = cipherText[i] - trueKey[i];
        temp += temp < 0 ? 26 : 0;

        temp += CHAR_OFFSET;

        plainText[i] = (char) temp;
    }
}
