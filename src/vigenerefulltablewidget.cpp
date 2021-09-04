#include <include/vigenerefulltablewidget.h>
#include "ui_vigenerefulltablewidget.h"

#include <cstring>
#include <iostream>

VigenereFullTableWidget::VigenereFullTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VigenereFullTableWidget)
{
    ui->setupUi(this);

    ui->tableAlphabetView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableAlphabetView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

    model = nullptr;
}

VigenereFullTableWidget::~VigenereFullTableWidget()
{
    delete model;
    delete ui;
}

void VigenereFullTableWidget::setAlphabetTable(std::vector<std::vector<char>> table)
{
    if (model != nullptr) delete model;

    for (int i = 0; i < 26; i++) {
        std::vector<char> temp(table[i]);
        alphabetTable.push_back(temp);
    }

    model = new QStandardItemModel(26, 26, this);

    model->setHeaderData(0, Qt::Orientation::Horizontal, QObject::tr("PT_A"));
    model->setHeaderData(1, Qt::Orientation::Horizontal, QObject::tr("PT_B"));
    model->setHeaderData(2, Qt::Orientation::Horizontal, QObject::tr("PT_C"));
    model->setHeaderData(3, Qt::Orientation::Horizontal, QObject::tr("PT_D"));
    model->setHeaderData(4, Qt::Orientation::Horizontal, QObject::tr("PT_E"));
    model->setHeaderData(5, Qt::Orientation::Horizontal, QObject::tr("PT_F"));
    model->setHeaderData(6, Qt::Orientation::Horizontal, QObject::tr("PT_G"));
    model->setHeaderData(7, Qt::Orientation::Horizontal, QObject::tr("PT_H"));
    model->setHeaderData(8, Qt::Orientation::Horizontal, QObject::tr("PT_I"));
    model->setHeaderData(9, Qt::Orientation::Horizontal, QObject::tr("PT_J"));
    model->setHeaderData(10, Qt::Orientation::Horizontal, QObject::tr("PT_K"));
    model->setHeaderData(11, Qt::Orientation::Horizontal, QObject::tr("PT_L"));
    model->setHeaderData(12, Qt::Orientation::Horizontal, QObject::tr("PT_M"));
    model->setHeaderData(13, Qt::Orientation::Horizontal, QObject::tr("PT_N"));
    model->setHeaderData(14, Qt::Orientation::Horizontal, QObject::tr("PT_O"));
    model->setHeaderData(15, Qt::Orientation::Horizontal, QObject::tr("PT_P"));
    model->setHeaderData(16, Qt::Orientation::Horizontal, QObject::tr("PT_Q"));
    model->setHeaderData(17, Qt::Orientation::Horizontal, QObject::tr("PT_R"));
    model->setHeaderData(18, Qt::Orientation::Horizontal, QObject::tr("PT_S"));
    model->setHeaderData(19, Qt::Orientation::Horizontal, QObject::tr("PT_T"));
    model->setHeaderData(20, Qt::Orientation::Horizontal, QObject::tr("PT_U"));
    model->setHeaderData(21, Qt::Orientation::Horizontal, QObject::tr("PT_V"));
    model->setHeaderData(22, Qt::Orientation::Horizontal, QObject::tr("PT_W"));
    model->setHeaderData(23, Qt::Orientation::Horizontal, QObject::tr("PT_X"));
    model->setHeaderData(24, Qt::Orientation::Horizontal, QObject::tr("PT_Y"));
    model->setHeaderData(25, Qt::Orientation::Horizontal, QObject::tr("PT_Z"));

    model->setHeaderData(0, Qt::Orientation::Vertical, QObject::tr("KEY_A"));
    model->setHeaderData(1, Qt::Orientation::Vertical, QObject::tr("KEY_B"));
    model->setHeaderData(2, Qt::Orientation::Vertical, QObject::tr("KEY_C"));
    model->setHeaderData(3, Qt::Orientation::Vertical, QObject::tr("KEY_D"));
    model->setHeaderData(4, Qt::Orientation::Vertical, QObject::tr("KEY_E"));
    model->setHeaderData(5, Qt::Orientation::Vertical, QObject::tr("KEY_F"));
    model->setHeaderData(6, Qt::Orientation::Vertical, QObject::tr("KEY_G"));
    model->setHeaderData(7, Qt::Orientation::Vertical, QObject::tr("KEY_H"));
    model->setHeaderData(8, Qt::Orientation::Vertical, QObject::tr("KEY_I"));
    model->setHeaderData(9, Qt::Orientation::Vertical, QObject::tr("KEY_J"));
    model->setHeaderData(10, Qt::Orientation::Vertical, QObject::tr("KEY_K"));
    model->setHeaderData(11, Qt::Orientation::Vertical, QObject::tr("KEY_L"));
    model->setHeaderData(12, Qt::Orientation::Vertical, QObject::tr("KEY_M"));
    model->setHeaderData(13, Qt::Orientation::Vertical, QObject::tr("KEY_N"));
    model->setHeaderData(14, Qt::Orientation::Vertical, QObject::tr("KEY_O"));
    model->setHeaderData(15, Qt::Orientation::Vertical, QObject::tr("KEY_P"));
    model->setHeaderData(16, Qt::Orientation::Vertical, QObject::tr("KEY_Q"));
    model->setHeaderData(17, Qt::Orientation::Vertical, QObject::tr("KEY_R"));
    model->setHeaderData(18, Qt::Orientation::Vertical, QObject::tr("KEY_S"));
    model->setHeaderData(19, Qt::Orientation::Vertical, QObject::tr("KEY_T"));
    model->setHeaderData(20, Qt::Orientation::Vertical, QObject::tr("KEY_U"));
    model->setHeaderData(21, Qt::Orientation::Vertical, QObject::tr("KEY_V"));
    model->setHeaderData(22, Qt::Orientation::Vertical, QObject::tr("KEY_W"));
    model->setHeaderData(23, Qt::Orientation::Vertical, QObject::tr("KEY_X"));
    model->setHeaderData(24, Qt::Orientation::Vertical, QObject::tr("KEY_Y"));
    model->setHeaderData(25, Qt::Orientation::Vertical, QObject::tr("KEY_Z"));

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            model->setItem(i, j, new QStandardItem(QString(alphabetTable[i][j])));
        }
    }

    ui->tableAlphabetView->setModel(model);
}

void VigenereFullTableWidget::on_backButton_clicked()
{
    close();
}

