#include "../include/mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>
#include <QDebug>

#include <include/playfairwidget.h>

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
    vigenereItem->appendRow(new QStandardItem("Extended, 256 ASCII"));
    treeViewModel->appendRow(vigenereItem);
    treeViewModel->appendRow(new QStandardItem("Playfair Cipher"));
    treeViewModel->appendRow(new QStandardItem("Affine Cipher"));
    treeViewModel->appendRow(new QStandardItem("Enigma Cipher"));

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
    QStandardItem *temp = treeViewModel->itemFromIndex(index);

    qInfo() << temp->text();
}

