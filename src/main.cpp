#include <QApplication>
#include "MyScene.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    srand (time(NULL));
    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
