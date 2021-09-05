#include <include/affinewidget.h>
#include "ui_affinewidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <fstream>
#include <stdexcept>

#include <include/cipher/util.h>

AffineWidget::AffineWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AffineWidget)
{
    ui->setupUi(this);

    ui->sourceComboBox->addItem("keyboard");
    ui->sourceComboBox->addItem("file");

    ui->textTypeContainer_2->setVisible(false);
    ui->textTypeComboBox->addItem("plaintext");
    ui->textTypeComboBox->addItem("ciphertext");

    ui->fileContainer->setVisible(false);
    ui->keyboardContainer->setVisible(true);

    ui->decryptButton->setVisible(true);
    ui->encryptButton->setVisible(true);

    ui->aKeyText->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->bKeyText->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

    cipher = nullptr;
}

AffineWidget::~AffineWidget()
{
    delete ui;
    if (cipher != nullptr) delete cipher;
}

void AffineWidget::encrypt(unsigned int a, unsigned int b, std::string plainText)
{
    if (cipher != nullptr) delete cipher;
    cipher = new AffineCipher(a, b);

    cipher->setPlainText(plainText);

    cipher->encrypt();
}

void AffineWidget::decrypt(unsigned int a, unsigned int b, std::string cipherText)
{
    if (cipher != nullptr) delete cipher;
    cipher = new AffineCipher(a, b);

    cipher->setCipherText(cipherText);

    cipher->decrypt();
}

std::string AffineWidget::readFile(std::string fileName)
{
    std::ifstream fileInput(fileName.c_str(), std::ios::binary);
    std::ostringstream buffer;

    buffer << fileInput.rdbuf();

    std::string content = buffer.str();

    fileInput.close();

    return content;
}

void AffineWidget::handleFileOutput(std::string fileName, std::string content)
{
    std::ofstream fileOutput(fileName, std::ios::binary | std::ios::trunc);

    fileOutput << content;

    fileOutput.close();
}

QString AffineWidget::constructAsciiString(std::string text)
{
    QString s;
    for (int i = 0; i < text.length(); i++) {
        s += QChar(text[i]);
    }

    return s;
}

void AffineWidget::on_sourceComboBox_currentIndexChanged(int index)
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

void AffineWidget::on_textTypeComboBox_currentIndexChanged(int index)
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


void AffineWidget::on_browseFileInput_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        ui->fileInputText->setText(fileName);
    }

    delete dialog;
}


void AffineWidget::on_browseFileOutput_clicked()
{
    QFileDialog *dialog = new QFileDialog;

    QString fileName = dialog->getOpenFileName();
    if (!fileName.isNull()) {
        ui->fileOutputText->setText(fileName);
    }

    delete dialog;
}

void AffineWidget::on_encryptButton_clicked()
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

        int a;
        int b;

        a = std::stoul(ui->aKeyText->text().toLatin1().toStdString());
        b = std::stoul(ui->bKeyText->text().toLatin1().toStdString());

        if (!(CipherUtil::isRelativelyPrime(a, 256))) {
            throw std::runtime_error("a key is not relatively prime to 256");
        }
        if (content.length() == 0) {
            throw std::runtime_error("Plaintext length is zero");
        }

        encrypt(a, b, content);

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


void AffineWidget::on_decryptButton_clicked()
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

        int a;
        int b;

        a = std::stoul(ui->aKeyText->text().toLatin1().toStdString());
        b = std::stoul(ui->bKeyText->text().toLatin1().toStdString());

        if (!(CipherUtil::isRelativelyPrime(a, 256))) {
            throw std::runtime_error("a key is not relatively prime to 256");
        }
        if (content.length() == 0) {
            throw std::runtime_error("Plaintext length is zero");
        }

        decrypt(a, b, content);

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

