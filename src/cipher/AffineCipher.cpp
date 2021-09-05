#include <include/cipher/AffineCipher.h>

#include <sstream>

AffineCipher::AffineCipher(int a, int b)
{
    this->a = a;
    this->b = b;
}

void AffineCipher::setCipherText(std::string text) { cipherText = text; }
void AffineCipher::setPlainText(std::string text) { plainText = text; }
std::string AffineCipher::getCipherText(bool isSpaced) {
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
std::string AffineCipher::getPlainText() { return plainText; }

int AffineCipher::modularInverse(int a, int m)
{
    for (int i = 1; i < m; i++) {
        if ((((a % m) * (i % m)) % m) == 1) {
            return i;
        }
    }

    return -1;
}

void AffineCipher::encrypt()
{
    cipherText = plainText;
    for (int i = 0; i < cipherText.length(); i++) {
        cipherText[i] = (a * cipherText[i] + b) % 256;
    }
}

void AffineCipher::decrypt()
{
    plainText = cipherText;
    for (int i = 0; i < plainText.length(); i++) {
        plainText[i] = (modularInverse(a, 256) * (cipherText[i] - b)) % 256;
    }
}
