#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QString>
#include "DBConnection.h"

namespace Ui {
class SignIn;
}

class SignIn : public QDialog
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr, Conexao *db = nullptr);
    ~SignIn();

private slots:
    void on_signinButton_clicked();

private:
    Conexao *con;
    Ui::SignIn *ui;
};

#endif // SIGNIN_H
