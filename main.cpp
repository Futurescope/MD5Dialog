#include "MD5Dialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MD5Dialog dlg;
	dlg.show();
    return app.exec();
}
