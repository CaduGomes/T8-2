#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QTextStream>

void MainWindow::LoadDatabase(QVector<User *> &users, QVector<Document *> &documents){

    m_documents.clear();
    m_users.clear();

    if(!con->abrir()){
        QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
    }else{
        QSqlQuery query;
        query.prepare("SELECT * from users");
        if(query.exec()){
            while(query.next()){
                QString name = query.value(1).toString();
                QString pwd = query.value(2).toString();
                QString id = query.value(0).toString();

                users.push_back(new User(name, pwd, id));
            }

        } else {
            QMessageBox::warning(this, "Erro", "Query não executada");
        }
    }


    if(!con->abrir()){
        QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
    }else{
        QSqlQuery query, query2;
        query.prepare("SELECT * from documents");
        if(query.exec()){
            while(query.next()){
                QString docID = query.value(0).toString();
                QString docName = query.value(1).toString();
                QString docDirectory = query.value(2).toString();
                QString ownerId = query.value(3).toString();
                QVector<Signature *> docUsers;
                User *user;

                query2.prepare("SELECT * from signatures where id_document='"+docID+"'");
                if(query2.exec()){
                    while(query2.next()){
                        QString userId = query2.value(1).toString();
                        bool isSign = (query2.value(2).toString() == "1" ? true : false);
                        for(User *u : users){
                            if(u->getCPF() == userId){
                                docUsers.push_back(new Signature(u, isSign));
                            }
                        }

                    }
                }

                for(User *u : users){
                    if(u->getCPF() == ownerId){
                        user = u;
                    }
                }

                if(user->getCPF().length() > 0){
                    documents.push_back(new Document(docID, docDirectory,docName,user,docUsers));
                }

            }



        } else {
            QMessageBox::warning(this, "Erro", "Query não executada");
        }
    }
}

MainWindow::MainWindow(QWidget *parent, Conexao *db, QString authId) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    con = db;

    ui->setupUi(this);
    this->setWindowTitle("Principal");
    LoadDatabase(m_users, m_documents);

    for(User *u : m_users){
        if(u->getCPF() == authId){
            m_authUser = u;
        }
    }

    ui->TabsContainer->setTabText(0,"Meus Documentos");
    ui->TabsContainer->setTabText(1,"Adicionar Documentos");
    ui->TabsContainer->setTabText(2,"Assinar Documentos");
    ui->TabsContainer->setTabText(3,"About");

    for(Document *d : m_documents){
        if(d->getOwnerId() == authId){
            ui->docsList->addItem(d->getName());
        }
    }

    for(Document *d : m_documents){
        User *owner;
        for(User *u: m_users){
            if(d->getOwnerId() == u->getCPF()){
                owner = u;
            }
        }
        for(Signature *s : d->m_users){
            if(s->m_user->getCPF() == m_authUser->getCPF()){
                if(!s->getIsSigned()){
                    ui->docsToSignList->addItem("Nome: "+ d->getName()+"  -  Dono:  "+ owner->getName());
                }

            }
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_authUser;
    for(Document *d : m_documents){
        delete d;
    }
}

void MainWindow::on_selectDocButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        ui->docNameLabel->setText(fileName);
        file.close();
    }
}

void MainWindow::on_addDocButton_clicked()
{
    QString docDir = ui->docNameLabel->text();
    QString docName = ui->docNameInput->toPlainText();

    if(!con->abrir()){
        QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
    }else{
        QSqlQuery query;
        query.prepare("insert into documents (name, dir, id_owner) values" "('"+docName+"','"+docDir+"','"+m_authUser->getCPF()+"')");

        if(query.exec()){
            QString docID = query.lastInsertId().toString();
            for(Signature *s : m_addDocumentUsers){

                query.prepare("insert into signatures (id_user, sign, id_document) values" "('"+s->m_user->getCPF()+"',"+(s->getIsSigned() ? "true" : "false")+",'"+docID+"')");
                if(!query.exec()){
                    QMessageBox::warning(this, "Erro", "Signature insert error");
                }
            }

            con->fechar();

        }else {
            QMessageBox::warning(this, "Erro", "Document insert error");
        }
    }

    LoadDatabase(m_users, m_documents);
    m_addDocumentUsers.clear();
    ui->docNameInput->setText("Nenhum arquivo selecionado");
    ui->docNameInput->setText("");
    ui->userNameInput->setText("");
    QMessageBox::information(this, tr("Sucesso!"), tr("Documento adicionado com sucesso!"));
}

void MainWindow::on_addUserButton_clicked()
{
    QString userName = ui->userNameInput->toPlainText();
    bool find = false;
    for(User *u: m_users){
        if(u->getName() == userName){
            find = true;
            m_addDocumentUsers.push_back(new Signature(u, false));
        }
    }

    if(!find){
        QMessageBox::critical(this, tr("Erro"), tr("Usuário não encontrado!"));
    }else {
        ui->userNameInput->setText("");
        QMessageBox::information(this, tr("Sucesso!"), tr("Usuário adicionado com sucesso!"));
    }


}

void MainWindow::on_docsList_itemClicked(QListWidgetItem *item)
{
    ui->signList->clear();
    QString selectedItem = item->text();

    for(Document *d: m_documents){
        if(d->getName() == selectedItem){
            for(Signature *s : d->m_users){
                QString assinou = s->getIsSigned() ? "Sim": "Não";
                ui->signList->addItem("Nome: "+ s->m_user->getName()+" - Assinou: "+ assinou);
            }
        }
    }


}

void MainWindow::on_TabsContainer_tabBarClicked(int index)
{
    switch(index){
    case 0:
        ui->docsList->clear();
        ui->signList->clear();
        for(Document *d : m_documents){
            if(d->getOwnerId() == m_authUser->getCPF()){
                ui->docsList->addItem(d->getName());
            }
        }
        break;

    case 2:
        ui->docsToSignList->clear();
        for(Document *d : m_documents){
            User *owner;
            for(User *u: m_users){
                if(d->getOwnerId() == u->getCPF()){
                    owner = u;
                }
            }
            for(Signature *s : d->m_users){
                if(s->m_user->getCPF() == m_authUser->getCPF()){
                    if(!s->getIsSigned()){
                        ui->docsToSignList->addItem("Nome: "+ d->getName()+"  -  Dono:  "+ owner->getName());
                    }

                }
            }
        }
        break;

    default:
        break;
    }
}

void MainWindow::on_docsToSignList_itemDoubleClicked(QListWidgetItem *item)
{
    QString docName = item->text().split(" ")[1];
    QString docID = "";

    for(Document *d : m_documents){
        if(d->getName() == docName){
            docID = d->getID();
        }

    }

    if(!con->abrir()){
        QMessageBox::warning(this, "Erro", "Erro ao abrir o banco de dados");
    }else{
        QSqlQuery query;
        query.prepare("update signatures set sign=true where id_user='"+m_authUser->getCPF()+"' and id_document='"+docID+"'");
        if(query.exec()){
            con->fechar();
        }else {
            QMessageBox::warning(this, "Erro", "Document sign error");
        }
    }

    LoadDatabase(m_users, m_documents);
    on_TabsContainer_tabBarClicked(2);
    QMessageBox::information(this, tr("Sucesso!"), tr("Documento assinado com sucesso!"));

}


void MainWindow::on_actionUsuarios_triggered()
{
    DBShowData showUser(this,"users", con);

    showUser.exec();
}

void MainWindow::on_actionDocumentos_triggered()
{
    DBShowData showDocuments(this,"documents", con);

    showDocuments.exec();
}

void MainWindow::on_actionAssinaturas_triggered()
{
    DBShowData showSignatures(this,"signatures", con);

    showSignatures.exec();
}

void MainWindow::on_actionSignout_triggered()
{
    // Close user session
    close();
}
