#include <include/cipher/vigenere/VigenereRunningKey.h>

VigenereRunningKeyCipher::VigenereRunningKeyCipher(std::string key) : VigenereCipher(key)
{

}

void VigenereRunningKeyCipher::encrypt()
{
    std::string trueKey = key.substr(0, plainText.length());

    cipherText = plainText;
    for (int i = 0; i < cipherText.length(); i++) {
        cipherText[i] = (cipherText[i] + trueKey[i] - CHAR_OFFSET * 2) % 26 + CHAR_OFFSET;
    }
}

void VigenereRunningKeyCipher::decrypt()
{
    std::string trueKey = key.substr(0, cipherText.length());

    plainText = cipherText;
    for (int i = 0; i < plainText.length(); i++) {
        int temp = cipherText[i] - trueKey[i];
        temp += temp < 0 ? 26 : 0;

        temp += CHAR_OFFSET;

        plainText[i] = (char) temp;
    }
}
