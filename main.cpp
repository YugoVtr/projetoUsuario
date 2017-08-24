#include "janelaPrincipal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    janelaPrincipal w;
    w.show();

    return a.exec();
}
