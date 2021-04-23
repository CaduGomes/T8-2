#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "mainwindow.h"
#include "DBConnection.h"
#include "signin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr, Conexao *db = nullptr);
    ~Login();

private slots:
    void on_loginButton_clicked();

    void on_signinButton_clicked();

protected:
     Conexao *con;

private:
    Ui::Login *ui;
    MainWindow *main;
    SignIn *signin;
};
#endif // LOGIN_H
