#ifndef VIGENERESTANDARDWIDGET_H
#define VIGENERESTANDARDWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class VigenereStandardWidget; }
QT_END_NAMESPACE

class VigenereStandardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VigenereStandardWidget(QWidget *parent = nullptr);
    ~VigenereStandardWidget();
private:
    Ui::VigenereStandardWidget *ui;
signals:

};

#endif // VIGENERESTANDARDWIDGET_H
