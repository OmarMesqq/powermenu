#include <QApplication>
#include "mainWindow.h"
#include "constants.h"


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    app.setStyleSheet(R"(
        QWidget {
            background-color: #1e1e1e;
            color: #e6e6e6;
        }
        QPushButton {
            background-color: #2b2b2b;
            color: #e6e6e6;
        }
        QPushButton:hover {
            background-color: #343434;
        }
        QLabel {
            color: #e6e6e6;
        }
    )");

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
    } else if (args.contains("-l")) {
        mainWindow.logoutButton->setChecked(true);
        mainWindow.startCountdown(LOGOUT_STRING);
    }

    mainWindow.show();

    return app.exec();
}
