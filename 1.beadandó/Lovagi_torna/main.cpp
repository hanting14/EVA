#include "lovagitorna.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lovagiTorna w;
    w.show();
    return a.exec();
}
