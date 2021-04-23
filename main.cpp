#include <QApplication>
#include "selectdatabase.h"
#include "login.h"

Login *login;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectDatabase w;
    w.show();
    return a.exec();
}
