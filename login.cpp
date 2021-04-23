#include "login.h"
#include "ui_login.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

Login::Login(QWidget *parent, Conexao *db)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    con = db;
}

Login::~Login()
{
    delete ui;
    delete main;
    delete signin;
}


void Login::on_loginButton_clicked()
{
    QString name = ui->nameInput->toPlainText();
    QString pwd = ui->pwdInput->toPlainText();
    QMessageBox box;
    if(name.length() > 0 && pwd.length() > 0){

        if(!con->abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
        }else{
            QSqlQuery query;
            query.prepare("SELECT * from users where name='"+name+"' and PWD='"+pwd+"'");
            if(query.exec()){
                query.first();
                if(query.value(1).toString()!=""){
                    box.setText("Logado com sucesso!");
                    box.exec();
                    this->close();
                    main = new MainWindow(0, con, query.value(0).toString());

                    main->show();

                }else {
                    box.setText("Conta não encontrada!");
                    box.exec();
                    return;
                }

            } else {
                QMessageBox::warning(this, "Erro", "Query não executada");
            }
        }

    }else {
        box.setText("Campos obrigatórios!");
        box.exec();
        return;
    }

}

void Login::on_signinButton_clicked()
{
    signin = new SignIn(this, con);
    signin->exec();
}
