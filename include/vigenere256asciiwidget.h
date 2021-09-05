#ifndef VIGENERE256ASCIIWIDGET_H
#define VIGENERE256ASCIIWIDGET_H

#include <QWidget>
#include <include/cipher/vigenere/Vigenere256ASCII.h>

namespace Ui {
class Vigenere256AsciiWidget;
}

class Vigenere256AsciiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Vigenere256AsciiWidget(QWidget *parent = nullptr);
    ~Vigenere256AsciiWidget();

private slots:
    void on_sourceComboBox_currentIndexChanged(int index);
    void on_browseFileInput_clicked();
    void on_browseFileOutput_clicked();
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void on_browseKey_clicked();
    void on_keySourceComboBox_currentIndexChanged(int index);
    void on_textTypeComboBox_currentIndexChanged(int index);

private:
    std::string readFile(std::string);
    void encrypt(std::string, std::string);
    void decrypt(std::string, std::string);
    void handleFileOutput(std::string, std::string);
    QString constructAsciiString(std::string);

    Ui::Vigenere256AsciiWidget *ui;
    Vigenere256ASCIICipher *cipher;
};

#endif // VIGENERE256ASCIIWIDGET_H
