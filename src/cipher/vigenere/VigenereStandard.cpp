#include <include/cipher/vigenere/VigenereStandard.h>
#include <algorithm>

VigenereStandardCipher::VigenereStandardCipher(std::string key) : VigenereCipher(key)
{

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
