#include <include/vigenere256asciiwidget.h>
#include "ui_vigenere256asciiwidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <stdexcept>

#include <include/cipher/util.h>

Vigenere256AsciiWidget::Vigenere256AsciiWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vigenere256AsciiWidget)
{
    ui->setupUi(this);

    ui->sourceComboBox->addItem("keyboard");
    ui->sourceComboBox->addItem("file");

    ui->keySourceComboBox->addItem("keyboard");
    ui->keySourceComboBox->addItem("file");

    ui->browseKey->setVisible(false);

    ui->textTypeContainer_2->setVisible(false);
    ui->textTypeComboBox->addItem("plaintext");
    ui->textTypeComboBox->addItem("ciphertext");

    ui->fileContainer->setVisible(false);
    ui->keyboardContainer->setVisible(true);

    ui->decryptButton->setVisible(true);
    ui->encryptButton->setVisible(true);

    cipher = nullptr;
}

Vigenere256AsciiWidget::~Vigenere256AsciiWidget()
{
    delete ui;
    if (cipher != nullptr) delete cipher;
}

void Vigenere256AsciiWidget::encrypt(std::string key, std::string plainText)
{
    if (cipher != nullptr) delete cipher;
    cipher = new Vigenere256ASCIICipher(key);

    cipher->setPlainText(plainText);

    cipher->encrypt();
}

void Vigenere256AsciiWidget::decrypt(std::string key, std::string cipherText)
{
    if (cipher != nullptr) delete cipher;
    cipher = new Vigenere256ASCIICipher(key);

    cipher->setCipherText(cipherText);

    cipher->decrypt();
}

std::string Vigenere256AsciiWidget::readFile(std::string fileName)
{
    std::ifstream fileInput(fileName.c_str(), std::ios::binary);
    std::ostringstream buffer;

    buffer << fileInput.rdbuf();

    std::string content = buffer.str();

    fileInput.close();

    return content;
}

void Vigenere256AsciiWidget::handleFileOutput(std::string fileName, std::string content)
{
    std::ofstream fileOutput(fileName, std::ios::binary | std::ios::trunc);

    fileOutput << content;

    fileOutput.close();
}

QString Vigenere256AsciiWidget::constructAsciiString(std::string text)
{
    QString s;
    for (int i = 0; i < text.length(); i++) {
        s += QChar(text[i]);
    }

    return s;
}

void Vigenere256AsciiWidget::on_sourceComboBox_currentIndexChanged(int index)
{
    switch(index) {
        case 0: {
            ui->textTypeContainer_2->setVisible(false);
            ui->fileContainer->setVisible(false);
            ui->keyboardContainer->setVisible(true);
            ui->verticalSpacer->changeSize(20, 40, QSizePolicy::Preferred, QSizePolicy::Expanding);

            ui->decryptButton->setVisible(true);
            ui->encryptButton->setVisible(true);
            break;
        }
        case 1: {
            ui->textTypeContainer_2->setVisible(true);
            ui->fileContainer->setVisible(true);
            ui->keyboardContainer->setVisible(false);
            ui->verticalSpacer->changeSize(20, 9, QSizePolicy::Minimum, QSizePolicy::Fixed);

            on_textTypeComboBox_currentIndexChanged(ui->textTypeComboBox->currentIndex());
            break;
        }
    }
}

void Vigenere256AsciiWidget::on_keySourceComboBox_currentIndexChanged(int index)
{
    ui->keyTextBox->clear();
    switch(index) {
        case 0: {
            ui->browseKey->setVisible(false);
            break;
        }
        case 1: {
            ui->browseKey->setVisible(true);
            break;
        }
    }
}

void Vigenere256AsciiWidget::on_textTypeComboBox_currentIndexChanged(int index)
{
    switch(index) {
        case 0: {
            ui->decryptButton->setVisible(false);
            ui->encryptButton->setVisible(true);
            break;
        }
        case 1: {
            ui->decryptButton->setVisible(true);
            ui->encryptButton->setVisible(false);
            break;
        }
    }
}


void Vigenere256AsciiWidget::on_browseFileInput_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        ui->fileInputText->setText(fileName);
    }

    delete dialog;
}


void Vigenere256AsciiWidget::on_browseFileOutput_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        ui->fileOutputText->setText(fileName);
    }

    delete dialog;
}

void Vigenere256AsciiWidget::on_browseKey_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        ui->keyTextBox->setText(fileName);
    }

    delete dialog;
}

void Vigenere256AsciiWidget::on_encryptButton_clicked()
{
    try {
        std::string content;
        int contentSourceFlag = ui->sourceComboBox->currentIndex();
        if (contentSourceFlag == 0) {
            content = ui->plainTextBox->toPlainText().toStdString();
        } else {
            if (ui->fileInputText->text().toStdString().length() == 0) {
                throw std::runtime_error("File input is empty");
            }
            if (ui->fileOutputText->text().toStdString().length() == 0) {
                throw std::runtime_error("File output is empty");
            }
            content = readFile(ui->fileInputText->text().toStdString());
        }

        std::string key;
        if (ui->keySourceComboBox->currentIndex() == 0) {
            key = ui->keyTextBox->text().toLatin1().data();
        } else {
            if (ui->keyTextBox->text().toStdString().length() == 0) {
                throw std::runtime_error("Key file input is empty");
            }
            key = readFile(ui->keyTextBox->text().toStdString());
        }

        if (key.length() == 0) {
            throw std::runtime_error("Key length is zero");
        }
        if (content.length() == 0) {
            throw std::runtime_error("Plaintext length is zero");
        }

        encrypt(key, content);

        std::string transformedCipherText = cipher->getCipherText(false);

        if (contentSourceFlag == 0) {
            ui->cipherTextBox->setPlainText(constructAsciiString(transformedCipherText));
        } else {
            handleFileOutput(ui->fileOutputText->text().toStdString(), transformedCipherText);
        }
    }  catch (std::runtime_error message) {
        QMessageBox errorBox(QMessageBox::Icon::Critical, QString("Error"), QString(message.what()), QMessageBox::StandardButton::Ok);

        errorBox.exec();
    }
}


void Vigenere256AsciiWidget::on_decryptButton_clicked()
{
    try {
        std::string content;
        int contentSourceFlag = ui->sourceComboBox->currentIndex();
        if (contentSourceFlag == 0) {
            content = ui->cipherTextBox->toPlainText().toLatin1().data();
        } else {
            if (ui->fileInputText->text().toStdString().length() == 0) {
                throw std::runtime_error("File input is empty");
            }
            if (ui->fileOutputText->text().toStdString().length() == 0) {
                throw std::runtime_error("File output is empty");
            }
            content = readFile(ui->fileInputText->text().toStdString());
        }

        std::string key;
        if (ui->keySourceComboBox->currentIndex() == 0) {
            key = ui->keyTextBox->text().toLatin1().data();
        } else {
            if (ui->keyTextBox->text().toStdString().length() == 0) {
                throw std::runtime_error("Key file input is empty");
            }
            key = readFile(ui->keyTextBox->text().toStdString());
        }

        if (key.length() == 0) {
            throw std::runtime_error("Key length is zero");
        }
        if (content.length() == 0) {
            throw std::runtime_error("Ciphertext length is zero");
        }

        decrypt(key, content);

        std::string plainText = cipher->getPlainText();

        if (contentSourceFlag == 0) {
            ui->plainTextBox->setPlainText(QString(plainText.c_str()));
        } else {
            handleFileOutput(ui->fileOutputText->text().toStdString(), plainText);
        }
    } catch (std::runtime_error message) {
        QMessageBox errorBox(QMessageBox::Icon::Critical, QString("Error"), QString(message.what()), QMessageBox::StandardButton::Ok);

        errorBox.exec();
    }
}

