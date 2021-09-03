#include "../include/vigenerestandardwidget.h"
#include "./ui_vigenerestandardwidget.h"

VigenereStandardWidget::VigenereStandardWidget(QWidget *parent) : QWidget(parent), ui(new Ui::VigenereStandardWidget)
{
    ui->setupUi(this);
}

VigenereStandardWidget::~VigenereStandardWidget() {
    delete ui;
}
