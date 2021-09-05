#ifndef AFFINEWIDGET_H
#define AFFINEWIDGET_H

#include <QWidget>
#include <include/cipher/AffineCipher.h>

namespace Ui {
class AffineWidget;
}

class AffineWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AffineWidget(QWidget *parent = nullptr);
    ~AffineWidget();

private slots:
    void on_sourceComboBox_currentIndexChanged(int index);
    void on_browseFileInput_clicked();
    void on_browseFileOutput_clicked();
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void on_textTypeComboBox_currentIndexChanged(int index);

private:
    std::string readFile(std::string);
    void encrypt(unsigned int, unsigned int, std::string);
    void decrypt(unsigned int, unsigned int, std::string);
    void handleFileOutput(std::string, std::string);
    QString constructAsciiString(std::string);

    Ui::AffineWidget *ui;
    AffineCipher *cipher;
};

#endif // AFFINEWIDGET_H
