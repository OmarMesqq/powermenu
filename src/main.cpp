#include <QApplication>
#include "mainWindow.h"

#define SHUTDOWN_STRING "Shutdown"
#define RESTART_STRING "Restart"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    //CLI args
    QStringList args = QCoreApplication::arguments();
    if (args.contains("-s")) {
        mainWindow.shutdownButton->setChecked(true);
        mainWindow.startCountdown(SHUTDOWN_STRING);
    } else if (args.contains("-r")) {
        mainWindow.restartButton->setChecked(true);
        mainWindow.startCountdown(RESTART_STRING);
    }

    mainWindow.show();

    return app.exec();
}
