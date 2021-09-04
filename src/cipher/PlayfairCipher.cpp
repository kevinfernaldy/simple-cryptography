#include <include/cipher/PlayfairCipher.h>

#include <algorithm>
#include <sstream>

const std::vector<char> PlayfairCipher::ALPHABET({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'});

PlayfairCipher::PlayfairCipher(std::string key)
{
    std::vector<char> keyVector;
    for (int i = 0; i < key.length(); i++) {
        if (std::find(keyVector.begin(), keyVector.end(), key[i]) == keyVector.end()) {
            keyVector.push_back(key[i]);
        }
    }

    std::vector<char> alphabetList;
    for (int i = 0; i < ALPHABET.size(); i++) {
        if (std::find(keyVector.begin(), keyVector.end(), ALPHABET[i]) == keyVector.end()) {
            alphabetList.push_back(ALPHABET[i]);
        }
    }

    int counter = 0;
    for (std::vector<char>::iterator it = keyVector.begin(); it != keyVector.end(); it++) {
        keySquare[counter / 5][counter % 5] = *it;
        counter++;
    }

    for(int i = 0; i < alphabetList.size(); i++) {
        keySquare[counter / 5][counter % 5] = alphabetList[i];
        counter++;
    }
}

void PlayfairCipher::setCipherText(std::string text) { cipherText = text; }
void PlayfairCipher::setPlainText(std::string text) { plainText = text; }
std::string PlayfairCipher::getCipherText(bool isSpaced) {
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
std::string PlayfairCipher::getPlainText(bool isWithSplitter) {
    if (isWithSplitter) {
        return plainText;
    } else {
        std::string tempPlainText = plainText;
        std::remove(tempPlainText.begin(), tempPlainText.end(), splitter);

        return tempPlainText;
    }
}

bool PlayfairCipher::isNotInMap(std::map<char, int> map, char c)
{
    if (map.find(c) != map.end()) {
        return false;
    } else {
        return true;
    }
}

std::pair<int,int> PlayfairCipher::findInKeySquare(char c)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keySquare[i][j] == c) {
                return std::pair<int,int>(i, j);
            }
        }
    }

    return std::pair<int,int>(-1,-1);
}

void PlayfairCipher::encrypt()
{
    std::string transformedPlainText = plainText;

    // Replace J with I first
    std::replace(transformedPlainText.begin(), transformedPlainText.end(), 'J', 'I');

    // Insert splitter to repeating characters
    std::vector<int> indexToInsert;
    for (int i = 0; i < transformedPlainText.length(); i += 2) {
        if (i + 1 >= transformedPlainText.length()) {
            break;
        }

        if (transformedPlainText[i] == transformedPlainText[i+1]) {
            indexToInsert.push_back(i+1);
        }
    }
    for (int i = 0; i < indexToInsert.size(); i++) {
        transformedPlainText.insert(indexToInsert[i], sizeof(char), splitter);
    }

    // Add splitter to the end if length is odd
    if (transformedPlainText.length() % 2 == 1) {
        transformedPlainText += splitter;
    }

    // Perform encryption
    for (int i = 0; i < transformedPlainText.length(); i += 2) {
        std::pair<int,int> firstLetterLocation = findInKeySquare(transformedPlainText[i]);
        std::pair<int,int> secondLetterLocation = findInKeySquare(transformedPlainText[i+1]);

        if (firstLetterLocation.first == secondLetterLocation.first) {  // Same row
            cipherText += keySquare[firstLetterLocation.first][(firstLetterLocation.second + 1) % 5];
            cipherText += keySquare[secondLetterLocation.first][(secondLetterLocation.second + 1) % 5];
        } else if (firstLetterLocation.second == secondLetterLocation.second) { // Same column
            cipherText += keySquare[(firstLetterLocation.first + 1) % 5][firstLetterLocation.second];
            cipherText += keySquare[(secondLetterLocation.first + 1) % 5][secondLetterLocation.second];
        } else {    // Square
            cipherText += keySquare[firstLetterLocation.first][secondLetterLocation.second];
            cipherText += keySquare[secondLetterLocation.first][firstLetterLocation.second];
        }
    }
}

void PlayfairCipher::decrypt()
{
    // Perform decryption
    std::string transformedCipherText = cipherText;
    for (int i = 0; i < transformedCipherText.length(); i += 2) {
        std::pair<int,int> firstLetterLocation = findInKeySquare(transformedCipherText[i]);
        std::pair<int,int> secondLetterLocation = findInKeySquare(transformedCipherText[i+1]);

        if (firstLetterLocation.first == secondLetterLocation.first) {  // Same row
            plainText += keySquare[firstLetterLocation.first][(firstLetterLocation.second - 1 + 5) % 5];
            plainText += keySquare[secondLetterLocation.first][(secondLetterLocation.second - 1 + 5) % 5];
        } else if (firstLetterLocation.second == secondLetterLocation.second) { // Same column
            plainText += keySquare[(firstLetterLocation.first - 1 + 5) % 5][firstLetterLocation.second];
            plainText += keySquare[(secondLetterLocation.first - 1 + 5) % 5][secondLetterLocation.second];
        } else {    // Square
            plainText += keySquare[firstLetterLocation.first][secondLetterLocation.second];
            plainText += keySquare[secondLetterLocation.first][firstLetterLocation.second];
        }
    }
}
