#ifndef VIGENEREAUTOKEYWIDGET_H
#define VIGENEREAUTOKEYWIDGET_H

#include <QWidget>
#include <include/cipher/vigenere/VigenereAutoKey.h>

namespace Ui {
class VigenereAutoKeyWidget;
}

class VigenereAutoKeyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VigenereAutoKeyWidget(QWidget *parent = nullptr);
    ~VigenereAutoKeyWidget();

private:
    std::string readFile(std::string);
    void encrypt(std::string, std::string);
    void decrypt(std::string, std::string);
    void handleFileOutput(std::string, std::string);

    Ui::VigenereAutoKeyWidget *ui;
    VigenereAutoKeyCipher *cipher;

signals:

private slots:
    void on_sourceComboBox_currentIndexChanged(int index);
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void on_renderCipherTextBox_stateChanged(int arg1);
    void on_browseFileInputButton_clicked();
    void on_browseFileOutputButton_clicked();
};

#endif // VIGENEREAUTOKEYWIDGET_H
