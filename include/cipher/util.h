#ifndef CIPHERUTIL_H
#define CIPHERUTIL_H

#include <string>

namespace Cipher { class CipherUtil; }

class CipherUtil
{
public:
    static std::string preparePlainText(std::string);
    static std::string prepareKey(std::string);
    static std::string prepareCipherText(std::string);

    static void checkKey(std::string);
    static void checkCipherText(std::string);
    static void checkPlainText(std::string);

    static void checkRunningKey(std::string, std::string);

    static bool isPlainTextAlphanumeric(std::string);
    static bool isNotAlphanumeric(char c);
};

#endif // CIPHERUTIL_H
