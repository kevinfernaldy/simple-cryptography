#include "../include/vigenerestandardwidget.h"
#include "./ui_vigenerestandardwidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <iostream>

#include <include/cipher/util.h>

VigenereStandardWidget::VigenereStandardWidget(QWidget *parent) : QWidget(parent), ui(new Ui::VigenereStandardWidget)
{
    ui->setupUi(this);

    ui->sourceComboBox->addItem("keyboard");
    ui->sourceComboBox->addItem("file");

    ui->textTypeContainer_2->setVisible(false);
    ui->textTypeComboBox->addItem("plaintext");
    ui->textTypeComboBox->addItem("ciphertext");

    ui->fileHandlingContainer->setVisible(false);

    ui->plainTextWarningLabel->setVisible(false);

    cipher = nullptr;
}

VigenereStandardWidget::~VigenereStandardWidget() {
    delete ui;
    if (cipher != nullptr) delete cipher;
}

void VigenereStandardWidget::encrypt(std::string key, std::string plainText)
{
    if (cipher != nullptr) delete cipher;
    cipher = new VigenereStandardCipher(key);

    cipher->setPlainText(plainText);

    cipher->encrypt();
}

void VigenereStandardWidget::decrypt(std::string key, std::string cipherText)
{
    if (cipher != nullptr) delete cipher;
    cipher = new VigenereStandardCipher(key);

    cipher->setCipherText(cipherText);

    cipher->decrypt();
}

std::string VigenereStandardWidget::readFile(std::string fileName)
{
    std::ifstream fileInput(fileName.c_str());
    std::ostringstream buffer;

    buffer << fileInput.rdbuf();

    std::string content = buffer.str();

    fileInput.close();

    return content;
}

void VigenereStandardWidget::handleFileOutput(std::string fileName, std::string content)
{
    std::ofstream fileOutput(fileName);

    fileOutput << content;

    fileOutput.close();
}

void VigenereStandardWidget::on_encryptButton_clicked()
{
    ui->plainTextWarningLabel->setVisible(false);

    try {
        std::string plainText = ui->plainTextBox->toPlainText().toStdString();
        std::string key = ui->keyTexyBox->text().toStdString();

        CipherUtil::checkPlainText(plainText);
        CipherUtil::checkKey(key);

        if (!(CipherUtil::isPlainTextAlphanumeric(plainText))) {
            ui->plainTextWarningLabel->setVisible(true);
            plainText = CipherUtil::preparePlainText(plainText);
        }

        key = CipherUtil::prepareKey(key);

        ui->plainTextBox->setPlainText(QString(plainText.c_str()));

        encrypt(key, plainText);

        std::string convertedCipherText;
        if (ui->renderCipherTextBox->isChecked()) {
            convertedCipherText = cipher->getCipherText(false);
        } else {
            convertedCipherText = cipher->getCipherText(true);
        }

        ui->cipherTextBox->setPlainText(QString(convertedCipherText.c_str()));

        if (ui->sourceComboBox->currentIndex() == 1) {  // Source and dest is file
            std::string fileOutputName = ui->fileOutputTextBox->text().toStdString();
            if (fileOutputName.empty()) {
                fileOutputName = ui->fileInputTextBox->text().toStdString() + "_ENCRYPTED";
            }

            handleFileOutput(fileOutputName, convertedCipherText);
        }
    }  catch (std::runtime_error message) {
        QMessageBox errorBox(QMessageBox::Icon::Critical, QString("Error"), QString(message.what()), QMessageBox::StandardButton::Ok);

        errorBox.exec();
    }
}

void VigenereStandardWidget::on_decryptButton_clicked()
{
    ui->plainTextWarningLabel->setVisible(false);

    try {
        std::string cipherText = ui->cipherTextBox->toPlainText().toStdString();
        std::string key = ui->keyTexyBox->text().toStdString();

        CipherUtil::checkCipherText(cipherText);
        CipherUtil::checkKey(key);

        cipherText = CipherUtil::prepareCipherText(cipherText);
        key = CipherUtil::prepareKey(key);

        decrypt(key, cipherText);

        std::string convertedPlainText = cipher->getPlainText();
        ui->cipherTextBox->setPlainText(QString(convertedPlainText.c_str()));

        if (ui->sourceComboBox->currentIndex() == 1) {  // Source and dest is file
            std::string fileOutputName = ui->fileOutputTextBox->text().toStdString();
            if (fileOutputName.empty()) {
                fileOutputName = ui->fileInputTextBox->text().toStdString() + "_DECRYPTED";
            }

            handleFileOutput(fileOutputName, convertedPlainText);
        }
    }  catch (std::runtime_error message) {
        QMessageBox errorBox(QMessageBox::Icon::Critical, QString("Error"), QString(message.what()), QMessageBox::StandardButton::Ok);

        errorBox.exec();
    }
}

void VigenereStandardWidget::on_renderCipherTextBox_stateChanged(int arg1)
{
    switch(arg1) {
        case 2: {
            ui->cipherTextBox->setPlainText(QString(cipher->getCipherText(false).c_str()));
            break;
        }
        default: {
            ui->cipherTextBox->setPlainText(QString(cipher->getCipherText(true).c_str()));
            break;
        }
    }
}

void VigenereStandardWidget::on_sourceComboBox_currentIndexChanged(int index)
{
    switch(index) {
        case 0: {
            ui->textTypeContainer_2->setVisible(false);
            ui->fileHandlingContainer->setVisible(false);

            ui->cipherTextBox->setReadOnly(false);
            ui->plainTextBox->setReadOnly(false);
            break;
        }
        case 1: {
            ui->textTypeContainer_2->setVisible(true);
            ui->fileHandlingContainer->setVisible(true);

            ui->cipherTextBox->setReadOnly(true);
            ui->plainTextBox->setReadOnly(true);
            break;
        }
    }
}


void VigenereStandardWidget::on_browseFileInputButton_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        std::string content = readFile(fileName.toStdString());
        int textType = ui->textTypeComboBox->currentIndex();

        try {
            switch(textType) {
                case 0: {   // Plaintext
                    CipherUtil::checkPlainText(content);

                    if (!(CipherUtil::isPlainTextAlphanumeric(content))) {
                        ui->plainTextWarningLabel->setVisible(true);
                        content = CipherUtil::preparePlainText(content);
                    }

                    ui->plainTextBox->setPlainText(QString(content.c_str()));
                    break;
                }
                case 1: {   // Ciphertext
                    CipherUtil::checkCipherText(content);
                    ui->cipherTextBox->setPlainText(QString(content.c_str()));
                    break;
                }
            }

            ui->fileInputTextBox->setText(fileName);
        } catch (std::runtime_error message) {
            QMessageBox errorBox(QMessageBox::Icon::Critical, QString("Error"), QString(message.what()), QMessageBox::StandardButton::Ok);

            errorBox.exec();
        }
    }

    delete dialog;
}


void VigenereStandardWidget::on_browseFileOutputButton_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        ui->fileOutputTextBox->setText(fileName);
    }

    delete dialog;
}

