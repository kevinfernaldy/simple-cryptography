#ifndef VIGENERERUNNINGKEYWIDGET_H
#define VIGENERERUNNINGKEYWIDGET_H

#include <QWidget>
#include <include/cipher/vigenere/VigenereRunningKey.h>

namespace Ui {
class VigenereRunningKeyWidget;
}

class VigenereRunningKeyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VigenereRunningKeyWidget(QWidget *parent = nullptr);
    ~VigenereRunningKeyWidget();

private:
    std::string readFile(std::string);
    void encrypt(std::string, std::string);
    void decrypt(std::string, std::string);
    void handleFileOutput(std::string, std::string);

    Ui::VigenereRunningKeyWidget *ui;
    VigenereRunningKeyCipher *cipher;
signals:

private slots:
    void on_sourceComboBox_currentIndexChanged(int index);
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void on_renderCipherTextBox_stateChanged(int arg1);
    void on_browseFileInputButton_clicked();
    void on_browseFileOutputButton_clicked();
};

#endif // VIGENERERUNNINGKEYWIDGET_H
