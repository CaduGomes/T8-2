#include "selectdatabase.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectDatabase w;
    w.show();
    return a.exec();
}
