#include <include/vigenerefullwidget.h>
#include "./ui_vigenerefullwidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <fstream>

#include <include/cipher/util.h>

#include <include/vigenerefulltabledialog.h>

VigenereFullWidget::VigenereFullWidget(QWidget *parent) : QWidget(parent), ui(new Ui::VigenereFullWidget)
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

VigenereFullWidget::~VigenereFullWidget() {
    delete ui;
    if (cipher != nullptr) delete cipher;
}

void VigenereFullWidget::encrypt(std::string key, std::string plainText)
{
    if (cipher == nullptr) {
        cipher = new VigenereFullCipher(key);
    } else {
        cipher->setKey(key);
    }

    cipher->setPlainText(plainText);

    cipher->encrypt();
}

void VigenereFullWidget::decrypt(std::string key, std::string cipherText)
{
    if (cipher == nullptr) {
        cipher = new VigenereFullCipher(key);
    } else {
        cipher->setKey(key);
    }

    cipher->setCipherText(cipherText);

    cipher->decrypt();
}

std::string VigenereFullWidget::readFile(std::string fileName)
{
    std::ifstream fileInput(fileName.c_str());
    std::ostringstream buffer;

    buffer << fileInput.rdbuf();

    std::string content = buffer.str();

    fileInput.close();

    return content;
}

void VigenereFullWidget::handleFileOutput(std::string fileName, std::string content)
{
    std::ofstream fileOutput(fileName);

    fileOutput << content;

    fileOutput.close();
}

void VigenereFullWidget::on_encryptButton_clicked()
{
    ui->plainTextWarningLabel->setVisible(false);

    try {
        std::string plainText = ui->plainTextBox->toPlainText().toLatin1().data();
        std::string key = ui->keyTextBox->text().toLatin1().data();

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
            std::string fileOutputName = ui->fileOutputTextBox->text().toLatin1().data();
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

void VigenereFullWidget::on_decryptButton_clicked()
{
    ui->plainTextWarningLabel->setVisible(false);

    try {
        std::string cipherText = ui->cipherTextBox->toPlainText().toLatin1().data();
        std::string key = ui->keyTextBox->text().toLatin1().data();

        CipherUtil::checkCipherText(cipherText);
        CipherUtil::checkKey(key);

        cipherText = CipherUtil::prepareCipherText(cipherText);
        key = CipherUtil::prepareKey(key);

        decrypt(key, cipherText);

        std::string convertedPlainText = cipher->getPlainText();
        ui->plainTextBox->setPlainText(QString(convertedPlainText.c_str()));

        if (ui->sourceComboBox->currentIndex() == 1) {  // Source and dest is file
            std::string fileOutputName = ui->fileOutputTextBox->text().toLatin1().data();
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

void VigenereFullWidget::on_renderCipherTextBox_stateChanged(int arg1)
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

void VigenereFullWidget::on_sourceComboBox_currentIndexChanged(int index)
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


void VigenereFullWidget::on_browseFileInputButton_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        std::string content = readFile(fileName.toLatin1().data());
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


void VigenereFullWidget::on_browseFileOutputButton_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        ui->fileOutputTextBox->setText(fileName);
    }

    delete dialog;
}


void VigenereFullWidget::on_viewTableButton_clicked()
{
    if (cipher == nullptr) {
        cipher = new VigenereFullCipher("PLACEHOLDER");
    }

    VigenereFullTableDialog *widget = new VigenereFullTableDialog();

    widget->setAlphabetTable(cipher->getAlphabetArray());

    widget->exec();

    delete widget;
}


void VigenereFullWidget::on_regenerateTableButton_clicked()
{
    if (cipher == nullptr) {
        cipher = new VigenereFullCipher("PLACEHOLDER");
    } else {
        cipher->generateNewTable();
    }

    ui->plainTextBox->clear();
    ui->cipherTextBox->clear();
}

