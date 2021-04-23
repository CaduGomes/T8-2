#include "selectdatabase.h"
#include "ui_selectdatabase.h"
#include "DBConnection.h"
#include "login.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

extern Login * login;

SelectDatabase::SelectDatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDatabase)
{
    ui->setupUi(this);
    setWindowTitle("Banco de Dados");

    ui->SelectText->setText("Nenhum arquivo selecionado!");
}

SelectDatabase::~SelectDatabase()
{
    delete ui;
}

void SelectDatabase::on_Select_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Selecione seu banco de dados"),
                                                    QString(),
                                                    tr("Arquivos de banco de dados (*.db);"));
    if (fileName.isEmpty())
    {
        ui->SelectText->setText("Nenhum arquivo selecionado!");
        return;
    }

    ui->SelectText->setText(fileName);
}

void SelectDatabase::on_buttonBox_accepted()
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, tr("Erro"), tr("Não foi possível abrir o arquivo!"));
        return;
    }

    login = new Login(0, new Conexao(fileName));
    login->show();
}

void SelectDatabase::on_buttonBox_rejected()
{
    this->close();
}
