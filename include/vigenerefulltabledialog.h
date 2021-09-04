#ifndef VIGENEREFULLTABLEDIALOG_H
#define VIGENEREFULLTABLEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <vector>

namespace Ui {
class VigenereFullTableDialog;
}

class VigenereFullTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VigenereFullTableDialog(QDialog *parent = nullptr);
    ~VigenereFullTableDialog();

    void setAlphabetTable(std::vector<std::vector<char>>);

private slots:
    void on_backButton_clicked();

private:
    Ui::VigenereFullTableDialog *ui;

    std::vector<std::vector<char>> alphabetTable;
    QStandardItemModel *model;
};

#endif // VIGENEREFULLTABLEDIALOG_H
