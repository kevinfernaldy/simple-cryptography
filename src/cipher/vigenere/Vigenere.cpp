#include <sstream>
#include <include/cipher/vigenere/Vigenere.h>

VigenereCipher::VigenereCipher(std::string key)
{
    this->key = key;
}

void VigenereCipher::setPlainText(std::string text)
{
    plainText = text;
}

void VigenereCipher::setCipherText(std::string text)
{
    cipherText = text;
}

std::string VigenereCipher::getPlainText()
{
    return plainText;
}

std::string VigenereCipher::getCipherText(bool isSpaced)
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
