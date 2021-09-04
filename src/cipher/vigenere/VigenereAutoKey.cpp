#include <include/cipher/vigenere/VigenereAutoKey.h>

VigenereAutoKeyCipher::VigenereAutoKeyCipher(std::string key) : VigenereCipher(key)
{

}

void VigenereAutoKeyCipher::encrypt()
{
    std::string trueKey = key;
    if (trueKey.length() < plainText.length()) {
        trueKey += plainText.substr(0, plainText.length() - key.length());
    }

    cipherText = plainText;
    for (int i = 0; i < cipherText.length(); i++) {
        cipherText[i] = (cipherText[i] + trueKey[i] - CHAR_OFFSET * 2) % 26 + CHAR_OFFSET;
    }
}

void VigenereAutoKeyCipher::decrypt()
{
    plainText = key;

    for (int i = 0; i < cipherText.length(); i++) {
        int temp = cipherText[i] - plainText[i];
        temp += temp < 0 ? 26 : 0;

        temp += CHAR_OFFSET;

        plainText += (char) temp;
    }

    plainText.erase(0, key.length());
}
