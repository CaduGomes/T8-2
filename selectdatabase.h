#ifndef SELECTDATABASE_H
#define SELECTDATABASE_H

#include <QDialog>

namespace Ui {
class SelectDatabase;
}

class SelectDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDatabase(QWidget *parent = nullptr);
    ~SelectDatabase();

private slots:
    void on_Select_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SelectDatabase *ui;
    QString fileName;
};

#endif // SELECTDATABASE_H
