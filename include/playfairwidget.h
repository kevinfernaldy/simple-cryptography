#ifndef PLAYFAIRWIDGET_H
#define PLAYFAIRWIDGET_H

#include <QWidget>
#include <include/cipher/PlayfairCipher.h>

namespace Ui {
class PlayfairWidget;
}

class PlayfairWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayfairWidget(QWidget *parent = nullptr);
    ~PlayfairWidget();

private:
    std::string readFile(std::string);
    void encrypt(std::string, std::string);
    void decrypt(std::string, std::string);
    void handleFileOutput(std::string, std::string);

    Ui::PlayfairWidget *ui;
    PlayfairCipher *cipher;
signals:

private slots:
    void on_sourceComboBox_currentIndexChanged(int index);
    void on_encryptButton_clicked();
    void on_decryptButton_clicked();
    void on_renderCipherTextBox_stateChanged(int arg1);
    void on_browseFileInputButton_clicked();
    void on_browseFileOutputButton_clicked();
};

#endif // PLAYFAIRWIDGET_H
