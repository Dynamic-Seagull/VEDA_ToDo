#include "TodoWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TodoWindow w;

    w.show();

    return a.exec();
}
