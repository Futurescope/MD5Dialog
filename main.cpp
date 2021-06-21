#include "MD5Dialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MD5Dialog w;
    w.show();
    return a.exec();
}
