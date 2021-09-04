#include "../../include/cipher/util.h"
#include <algorithm>
#include <regex>
#include <stdexcept>

bool CipherUtil::isNotAlphanumeric(char c)
{
    return !std::isalpha(c);
}

std::string CipherUtil::preparePlainText(std::string plainText)
{
    plainText.erase(remove_if(plainText.begin(), plainText.end(), isNotAlphanumeric), plainText.end());
    std::transform(plainText.begin(), plainText.end(), plainText.begin(), ::toupper);

    return plainText;
}

std::string CipherUtil::prepareCipherText(std::string cipherText)
{
    return preparePlainText(cipherText);
}

std::string CipherUtil::prepareKey(std::string key)
{
    std::transform(key.begin(), key.end(), key.begin(), ::toupper);

    return key;
}


void CipherUtil::checkCipherText(std::string cipherText)
{
    if (!(cipherText.length() > 0)) {
        throw std::runtime_error("Cipher text length is zero");
    } else if (!(std::regex_match(cipherText, std::regex("^([a-zA-Z]|\\s)*$")))) {
        throw std::runtime_error("Cipher text is invalid. Only alphabet letters and spaces are allowed");
    }
}

void CipherUtil::checkKey(std::string key)
{
    if (!(key.length() > 0)) {
        throw std::runtime_error("Key length is zero");
    } else if (!(std::regex_match(key, std::regex("^([a-zA-Z])*$")))) {
        throw std::runtime_error("Key is invalid. Only alphabet letters are allowed");
    }
}

void CipherUtil::checkPlainText(std::string plainText)
{
    if (!(plainText.length() > 0)) {
        throw std::runtime_error("Plain text length is zero");
    }
}

bool CipherUtil::isPlainTextAlphanumeric(std::string plainText)
{
   return std::regex_match(plainText, std::regex("^([a-zA-Z])*$"));
}
