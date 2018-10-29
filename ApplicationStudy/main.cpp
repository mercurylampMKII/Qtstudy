#include "noteii.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Noteii note;
    note.show();

    return a.exec();
}
