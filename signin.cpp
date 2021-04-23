#include "signin.h"
#include "ui_signin.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

SignIn::SignIn(QWidget *parent, Conexao *db) :
    QDialog(parent),
    ui(new Ui::SignIn)
{
    con = db;
    ui->setupUi(this);
    setWindowTitle("Criar Conta");
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_signinButton_clicked()
{
    QString name = ui->nameInput->toPlainText();
    QString pwd = ui->passwordInput->toPlainText();
    QString id = ui->idInput->toPlainText();
    QMessageBox box;
    if(name.length() > 0 && pwd.length() >0){
        if(!con->abrir()){
         QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
        }else{
         QSqlQuery query;
         query.prepare("insert into users (CPF, Name, PWD) values" "('"+id+"','"+name+"','"+pwd+"')");
         if(query.exec()){
            box.setText("Conta criada com sucesso!");
            box.exec();
            hide();
            con->fechar();

         } else {
            QMessageBox::warning(this, "Erro", "Query não executada");
         }
        }

    }else{
        box.setText("Campos obrigatórios!");
        box.exec();
    }

}
