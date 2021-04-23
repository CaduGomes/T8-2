#include <QApplication>

#include "login.h"

Login *login;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login = new Login();
    login->show();
    return a.exec();
}
