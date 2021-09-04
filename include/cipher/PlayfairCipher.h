#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include <string>
#include <map>
#include <vector>

namespace Cipher { class PlayfairCipher; }

class PlayfairCipher
{
public:
    PlayfairCipher(std::string);

    void encrypt();
    void decrypt();

    void setCipherText(std::string);
    void setPlainText(std::string);
    std::string getCipherText(bool);
    std::string getPlainText(bool);
private:
    static bool isNotInMap(std::map<char, int>, char);
    static const std::vector<char> ALPHABET;
    std::pair<int,int> findInKeySquare(char c);

    std::string plainText;
    std::string cipherText;
    char keySquare[5][5];

    char splitter = 'Z';
};

#endif // PLAYFAIRCIPHER_H
