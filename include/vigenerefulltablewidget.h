#ifndef VIGENEREFULLTABLEWIDGET_H
#define VIGENEREFULLTABLEWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <vector>

namespace Ui {
class VigenereFullTableWidget;
}

class VigenereFullTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VigenereFullTableWidget(QWidget *parent = nullptr);
    ~VigenereFullTableWidget();

    void setAlphabetTable(std::vector<std::vector<char>>);

private slots:
    void on_backButton_clicked();

private:
    Ui::VigenereFullTableWidget *ui;

    std::vector<std::vector<char>> alphabetTable;
    QStandardItemModel *model;
};

#endif // VIGENEREFULLTABLEWIDGET_H
