#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql>

class Conexao{
public:
    QSqlDatabase bancoDeDados;
    QString banco;

 Conexao(QString endereco){
    banco = endereco;
    bancoDeDados = QSqlDatabase::addDatabase("QSQLITE");
 }

 void fechar(){
    bancoDeDados.close();
 }

 bool abrir(){
    bancoDeDados.setDatabaseName(banco);
    if(!bancoDeDados.open())
    {
        return false;
    }else{
        return true;
    }
  }

 bool aberto(){
    if(bancoDeDados.isOpen()){
        return true;
    }else{
        return false;
    }
  }



};



#endif // DBCONNECTION_H
