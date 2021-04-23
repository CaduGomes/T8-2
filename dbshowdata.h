#ifndef DBSHOWDATA_H
#define DBSHOWDATA_H

#include <QDialog>
#include "DBConnection.h"
namespace Ui {
class DBShowData;
}

class DBShowData : public QDialog
{
    Q_OBJECT

public:
    explicit DBShowData(QWidget *parent = nullptr, QString type = "", Conexao *db = nullptr);
    ~DBShowData();

private:
    Ui::DBShowData *ui;
    QString dataType;

    void refreshData();

    Conexao *con;
};

#endif // DBSHOWDATA_H
