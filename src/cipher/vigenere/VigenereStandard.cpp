#include <include/cipher/vigenere/VigenereStandard.h>
#include <algorithm>

VigenereStandardCipher::VigenereStandardCipher(std::string key) : VigenereCipher(key)
{

}

void VigenereStandardCipher::encrypt()
{
    cipherText = plainText;
    for (int i = 0; i < cipherText.length(); i++) {
        cipherText[i] = (cipherText[i] + key[i % key.length()] - CHAR_OFFSET * 2) % 26 + CHAR_OFFSET;
    }
}

void VigenereStandardCipher::decrypt()
{
    plainText = cipherText;
    for (int i = 0; i < plainText.length(); i++) {
        int temp = cipherText[i] - key[i % key.length()];
        temp += temp < 0 ? 26 : 0;

        temp += CHAR_OFFSET;

        plainText[i] = (char) temp;
    }
}
