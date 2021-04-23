#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "document.h"
#include "user.h"
#include "DBConnection.h"
#include <QVector>
#include <QMainWindow>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "dbshowdata.h";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, Conexao *db = nullptr, QString authId = "");
    ~MainWindow();

    QVector<User *> m_users;
    QVector <Document *> m_documents;

    void LoadDatabase(QVector<User *> &users, QVector <Document *> &documents);
    void saveDatabase(QVector<User *> users, QVector <Document *> documents);

private slots:
    void on_selectDocButton_clicked();

    void on_addDocButton_clicked();

    void on_addUserButton_clicked();

    void on_docsList_itemClicked(QListWidgetItem *item);

    void on_TabsContainer_tabBarClicked(int index);

    void on_docsToSignList_itemDoubleClicked(QListWidgetItem *item);

    void on_actionUsuarios_triggered();

    void on_actionDocumentos_triggered();

    void on_actionAssinaturas_triggered();

    void on_actionSignout_triggered();

private:
    User *m_authUser;
    Ui::MainWindow *ui;
    Conexao *con;
    QVector <Signature *> m_addDocumentUsers;
    DBShowData *showData;
};




#endif // MAINWINDOW_H
