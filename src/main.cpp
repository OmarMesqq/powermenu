#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QProcess>
#include <QMessageBox>
#include <QTimer>
#include <QLabel>
#include <QKeyEvent>

#define SHUTDOWN_STRING "Shutdown"
#define RESTART_STRING "Restart"

void shutdown();
void restart();

int countdown = 2;
QTimer *timer;
QLabel *label;
QString actionType;
QPushButton *buttonA;
QPushButton *buttonB;

void startCountdown(const QString &action) {
    actionType = action;
    label->setText(QString("%1 in: %2 seconds").arg(actionType).arg(countdown));
    timer->start(1000);
}


void updateCountdown() {
    if (countdown > 0) {
        countdown--;
        label->setText(QString("%1 in: %2 seconds").arg(actionType).arg(countdown));
    } else {
        timer->stop();
        if (actionType == SHUTDOWN_STRING) {
            shutdown();
        } else if (actionType == RESTART_STRING) {
            restart();
        }
    }
}

//this isnt working - pressing any key d
void cancelAction() {
    timer->stop();
    countdown = 10;
    label->setText("Action canceled.");
    buttonA->setChecked(false);
    buttonB->setChecked(false);
}

void keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        if (buttonA->isChecked()) {
            startCountdown(SHUTDOWN_STRING);
        } else if (buttonB->isChecked()) {
            startCountdown(RESTART_STRING);
        }
    } else {
        cancelAction();
    }
}

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QWidget mainWindow;
    mainWindow.setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);
    
    //TODO: hide this if no timer
    label = new QLabel("Press a button to start action...");
    layout->addWidget(label);

    buttonA = new QPushButton(SHUTDOWN_STRING);
    buttonB = new QPushButton(RESTART_STRING);

    layout->addWidget(buttonA);
    layout->addWidget(buttonB);
    mainWindow.setLayout(layout);
    
    mainWindow.resize(400, 100);

    // Timer for countdown
    timer = new QTimer(&mainWindow);
    QObject::connect(timer, &QTimer::timeout, updateCountdown);

    // Connect button signals
    QObject::connect(buttonA, &QPushButton::clicked, [&]() { shutdown(); });
    QObject::connect(buttonB, &QPushButton::clicked, [&]() { restart(); });

    // Parse command line arguments
    QStringList args = QCoreApplication::arguments();
    if (args.contains("-s")) {
        buttonA->setChecked(true);
        startCountdown(SHUTDOWN_STRING);
    } else if (args.contains("-r")) {
        buttonB->setChecked(true);
        startCountdown(RESTART_STRING);
    }

    mainWindow.show();

    return app.exec();
}

void shutdown() {
    // int ret = QProcess::execute("shutdown", QStringList() << "-h" << "now");
    int ret = QProcess::execute("echo", QStringList() << SHUTDOWN_STRING);
    if (ret != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to shutdown the system.");
    }
}

void restart() {
    // int ret = QProcess::execute("shutdown", QStringList() << "-r" << "now");
    int ret = QProcess::execute("echo", QStringList() << RESTART_STRING);
    if (ret != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to restart the system.");
    }
}
