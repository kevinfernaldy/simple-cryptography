#include <include/cipher/vigenere/Vigenere256ASCII.h>

Vigenere256ASCIICipher::Vigenere256ASCIICipher(std::string key) : VigenereCipher(key)
{

}

void Vigenere256ASCIICipher::encrypt()
{
    cipherText = plainText;
    for (int i = 0; i < cipherText.length(); i++) {
        unsigned int temp = ((unsigned char) cipherText[i] + (unsigned char) key[i % key.length()]) % 256;
        cipherText[i] = (unsigned char) temp;
    }
}

void Vigenere256ASCIICipher::decrypt()
{
    plainText = cipherText;
    for (int i = 0; i < plainText.length(); i++) {
        int temp = plainText[i] - key[i % key.length()];
        temp += temp < 0 ? 256 : 0;

        plainText[i] = (unsigned char) temp;
    }
}
