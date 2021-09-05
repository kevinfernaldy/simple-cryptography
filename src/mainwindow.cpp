#include "../include/mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDebug>

#include <include/affinewidget.h>
#include <include/playfairwidget.h>
#include <include/vigenere256asciiwidget.h>
#include <include/vigenereautokeywidget.h>
#include <include/vigenerefullwidget.h>
#include <include/vigenererunningkeywidget.h>
#include <include/vigenerestandardwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentWidget = new PlayfairWidget();
    ui->widgetContainerLayout->addWidget(currentWidget);

    // Set treeview model
    treeViewModel = new QStandardItemModel;
    QStandardItem *vigenereItem = new QStandardItem("Vigenère Cipher");
    vigenereItem->appendRow(new QStandardItem("Standard, 26 Alphabets"));
    vigenereItem->appendRow(new QStandardItem("Full, 26 Alphabets"));
    vigenereItem->appendRow(new QStandardItem("Auto-key, 26 Alphabets"));
    vigenereItem->appendRow(new QStandardItem("Running-key, 26 Alphabets"));
    vigenereItem->appendRow(new QStandardItem("Extended, 256 ASCII"));
    treeViewModel->appendRow(vigenereItem);
    treeViewModel->appendRow(new QStandardItem("Playfair Cipher"));
    treeViewModel->appendRow(new QStandardItem("Affine Cipher"));

    ui->treeView->setModel(treeViewModel);
    ui->treeView->setHeaderHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete currentWidget;
    delete treeViewModel;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if (index.parent().constInternalPointer() == nullptr && (index.row() > 0)) {
        ui->widgetContainerLayout->removeWidget(currentWidget);
        delete currentWidget;

        switch (index.row()) {
            case 1: {
                currentWidget = new PlayfairWidget();
                break;
            }
            case 2: {
                currentWidget = new AffineWidget();
                break;
            }
        }

        ui->widgetContainerLayout->addWidget(currentWidget);
    } else {
        ui->widgetContainerLayout->removeWidget(currentWidget);
        delete currentWidget;

        switch (index.row()) {
            case 0: {
                currentWidget = new VigenereStandardWidget();
                break;
            }
            case 1: {
                currentWidget = new VigenereFullWidget();
                break;
            }
            case 2: {
                currentWidget = new VigenereAutoKeyWidget();
                break;
            }
            case 3: {
                currentWidget = new VigenereRunningKeyWidget();
                break;
            }
            case 4: {
                currentWidget = new Vigenere256AsciiWidget();
                break;
            }
        }

        ui->widgetContainerLayout->addWidget(currentWidget);
    }
}

