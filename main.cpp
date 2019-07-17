#include "mainwindow.h"
#include <QApplication>

//Am british but using color is faster ;)

int main(int argc, char *argv[])
{
    bool noWindow;
    for (int i=0; i < argc; i++) {
        if (argv[i] == "-noWindow") {
            noWindow = false;
        } else {
            noWindow = true;
        }
    }



   /* if (noWindow) {

    } else {
        QApplication a(argc, argv);

        MainWindow w;

        w.show();

        return a.exec();
    }*/
    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
