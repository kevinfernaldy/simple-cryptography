#include "../include/viginerefullwidget.h"
#include "ui_viginerefullwidget.h"

ViginereFullWidget::ViginereFullWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViginereFullWidget)
{
    ui->setupUi(this);
}

ViginereFullWidget::~ViginereFullWidget()
{
    delete ui;
}
