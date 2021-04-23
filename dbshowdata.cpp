#include "dbshowdata.h"
#include "ui_dbshowdata.h"
#include <QTableWidgetItem>
#include <QMessageBox>

DBShowData::DBShowData(QWidget *parent, QString type, Conexao *db) :
    QDialog(parent),
    ui(new Ui::DBShowData)
{
    ui->setupUi(this);
    this->setWindowTitle("Banco de dados");
    dataType = type;
    con = db;
    refreshData();


}

DBShowData::~DBShowData()
{
    delete ui;
}

void DBShowData::refreshData(){

    if (dataType == "users") {

        if(!con->abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
        }else{
            QSqlQuery query;
            query.prepare("SELECT * from users");
            if(query.exec()){
                int row = 1;

                query.last();

                int size = query.at() +1;
                ui->table->setColumnCount(3);
                ui->table->setRowCount(size);

                QTableWidgetItem *newItem = new QTableWidgetItem(tr("CPF")); // Criando o item header
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable); // Torna os items não editaveis
                ui->table->setHorizontalHeaderItem(0, newItem);

                newItem = new QTableWidgetItem(tr("Nome"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(1, newItem);

                newItem = new QTableWidgetItem(tr("Senha"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(2, newItem);

                //First Item

                query.first();

                if(query.value(0).toString() !=""){
                    QString cpf = query.value(0).toString();
                    QString name = query.value(1).toString();
                    QString pwd = query.value(2).toString();

                    newItem = new QTableWidgetItem(cpf);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 0, newItem);

                    newItem = new QTableWidgetItem(name);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 1, newItem);

                    newItem = new QTableWidgetItem(pwd);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 2, newItem);

                    // ====================================

                    while(query.next()){
                        QString cpf = query.value(0).toString();
                        QString name = query.value(1).toString();
                        QString pwd = query.value(2).toString();

                        QTableWidgetItem *newItem = new QTableWidgetItem(cpf);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 0, newItem);

                        newItem = new QTableWidgetItem(name);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 1, newItem);

                        newItem = new QTableWidgetItem(pwd);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 2, newItem);

                        row++;
                    }
                }
            } else {
                QMessageBox::warning(this, "Erro", "Query não executada");
            }
        }

    }else if (dataType == "documents") {

        if(!con->abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
        }else{
            QSqlQuery query;
            query.prepare("SELECT * from documents");
            if(query.exec()){
                int row = 1;

                query.last();

                int size = query.at() + 1;
                ui->table->setColumnCount(4);
                ui->table->setRowCount(size);

                QTableWidgetItem *newItem = new QTableWidgetItem(tr("ID")); // Criando o item header
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable); // Torna os items não editaveis
                ui->table->setHorizontalHeaderItem(0, newItem);

                newItem = new QTableWidgetItem(tr("Nome"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(1, newItem);

                newItem = new QTableWidgetItem(tr("Diretorio"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(2, newItem);

                newItem = new QTableWidgetItem(tr("ID Dono"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(3, newItem);

                //First Item

                query.first();

                if(query.value(0).toString() !=""){
                    QString id = query.value(0).toString();
                    QString name = query.value(1).toString();
                    QString dir = query.value(2).toString();
                    QString id_owner = query.value(3).toString();

                    newItem = new QTableWidgetItem(id);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 0, newItem);

                    newItem = new QTableWidgetItem(name);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 1, newItem);

                    newItem = new QTableWidgetItem(dir);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 2, newItem);

                    newItem = new QTableWidgetItem(id_owner);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 3, newItem);

                    // ====================================

                    while(query.next()){
                        QString id = query.value(0).toString();
                        QString name = query.value(1).toString();
                        QString dir = query.value(2).toString();
                        QString id_owner = query.value(3).toString();

                        QTableWidgetItem *newItem = new QTableWidgetItem(id);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 0, newItem);

                        newItem = new QTableWidgetItem(name);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 1, newItem);

                        newItem = new QTableWidgetItem(dir);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 2, newItem);

                        newItem = new QTableWidgetItem(id_owner);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 3, newItem);

                        row++;
                    }
                }
            } else {
                QMessageBox::warning(this, "Erro", "Query não executada");
            }
        }

    }else if (dataType == "signatures") {

        if(!con->abrir()){
            QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
        }else{
            QSqlQuery query;
            query.prepare("SELECT * from signatures");
            if(query.exec()){
                int row = 1;

                query.last();

                int size = query.at() +1;
                ui->table->setColumnCount(4);
                ui->table->setRowCount(size);

                QTableWidgetItem *newItem = new QTableWidgetItem(tr("ID")); // Criando o item header
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable); // Torna os items não editaveis
                ui->table->setHorizontalHeaderItem(0, newItem);

                newItem = new QTableWidgetItem(tr("ID Usuário"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(1, newItem);

                newItem = new QTableWidgetItem(tr("Assinado"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(2, newItem);

                newItem = new QTableWidgetItem(tr("ID Documento"));
                newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                ui->table->setHorizontalHeaderItem(3, newItem);

                //First Item

                query.first();

                if(query.value(0).toString() !=""){
                    QString id = query.value(0).toString();
                    QString id_user = query.value(1).toString();
                    QString sign = query.value(2).toString() == "1" ? "Sim" : "Não";
                    QString id_document = query.value(3).toString();

                    newItem = new QTableWidgetItem(id);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 0, newItem);

                    newItem = new QTableWidgetItem(id_user);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 1, newItem);

                    newItem = new QTableWidgetItem(sign);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 2, newItem);

                    newItem = new QTableWidgetItem(id_document);
                    newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                    ui->table->setItem(0, 3, newItem);

                    // ====================================

                    while(query.next()){
                        QString id = query.value(0).toString();
                        QString id_user = query.value(1).toString();
                        QString sign = query.value(2).toString() == "1" ? "Sim" : "Não";
                        QString id_document = query.value(3).toString();

                        QTableWidgetItem *newItem = new QTableWidgetItem(id);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 0, newItem);

                        newItem = new QTableWidgetItem(id_user);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 1, newItem);

                        newItem = new QTableWidgetItem(sign);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 2, newItem);

                        newItem = new QTableWidgetItem(id_document);
                        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
                        ui->table->setItem(row, 3, newItem);

                        row++;
                    }
                }
            } else {
                QMessageBox::warning(this, "Erro", "Query não executada");
            }
        }
    }
}

void DBShowData::on_refreshButton_clicked()
{
    refreshData();
}
