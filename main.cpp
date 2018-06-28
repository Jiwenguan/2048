#include "G2048Dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    G2048Dialog w;
    w.show();

    return a.exec();
}
