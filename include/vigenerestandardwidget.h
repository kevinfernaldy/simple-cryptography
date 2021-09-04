#ifndef VIGENERESTANDARDWIDGET_H
#define VIGENERESTANDARDWIDGET_H

#include <QWidget>
#include <include/cipher/vigenere/VigenereStandard.h>

QT_BEGIN_NAMESPACE
namespace Ui { class VigenereStandardWidget; }
QT_END_NAMESPACE

class VigenereStandardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VigenereStandardWidget(QWidget *parent = nullptr);
    ~VigenereStandardWidget();
private:
    Ui::VigenereStandardWidget *ui;
    std::string readFile(std::string);
    void encrypt(std::string, std::string);
    void decrypt(std::string, std::string);
    void handleFileOutput(std::string, std::string);

    VigenereStandardCipher *cipher;
signals:

private slots:
    void on_sourceComboBox_currentIndexChanged(int index);
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void on_renderCipherTextBox_stateChanged(int arg1);
    void on_browseFileInputButton_clicked();
    void on_browseFileOutputButton_clicked();
};

#endif // VIGENERESTANDARDWIDGET_H
