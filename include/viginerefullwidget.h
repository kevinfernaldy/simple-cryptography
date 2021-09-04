#ifndef VIGINEREFULLWIDGET_H
#define VIGINEREFULLWIDGET_H

#include <QWidget>

namespace Ui {
class ViginereFullWidget;
}

class ViginereFullWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViginereFullWidget(QWidget *parent = nullptr);
    ~ViginereFullWidget();

private slots:

private:
    Ui::ViginereFullWidget *ui;
};

#endif // VIGINEREFULLWIDGET_H
