#ifndef VIGENEREFULLWIDGET_H
#define VIGENEREFULLWIDGET_H

#include <QWidget>
#include <include/cipher/vigenere/VigenereFull.h>

QT_BEGIN_NAMESPACE
namespace Ui { class VigenereFullWidget; }
QT_END_NAMESPACE

class VigenereFullWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VigenereFullWidget(QWidget *parent = nullptr);
    ~VigenereFullWidget();

private:
    std::string readFile(std::string);
    void encrypt(std::string, std::string);
    void decrypt(std::string, std::string);
    void handleFileOutput(std::string, std::string);

    Ui::VigenereFullWidget *ui;
    VigenereFullCipher *cipher;
signals:

private slots:
    void on_sourceComboBox_currentIndexChanged(int index);
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void on_renderCipherTextBox_stateChanged(int arg1);
    void on_browseFileInputButton_clicked();
    void on_browseFileOutputButton_clicked();
    void on_viewTableButton_clicked();
    void on_regenerateTableButton_clicked();
};

#endif // VIGENEREFULLWIDGET_H
