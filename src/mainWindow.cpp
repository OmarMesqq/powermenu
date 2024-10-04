#include "mainWindow.h"
#include "constants.h"
#include <QVBoxLayout>
#include <QProcess>
#include <QMessageBox>
#include <QKeyEvent>


void shutdown();
void restart();
void logout();

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), countdown(5) {
    timer = new QTimer(this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    label = new QLabel(nullptr);
    label->hide();
    layout->addWidget(label);

    shutdownButton = new QPushButton(SHUTDOWN_STRING);
    restartButton = new QPushButton(RESTART_STRING);
    logoutButton = new QPushButton(LOGOUT_STRING);

    layout->addWidget(shutdownButton);
    layout->addWidget(restartButton);
    layout->addWidget(logoutButton);

    setLayout(layout);
    resize(400, 100);

    // Timer setup
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCountdown);

    // Connect button signals
    connect(shutdownButton, &QPushButton::clicked, this, [&]() { startCountdown(SHUTDOWN_STRING); });
    connect(restartButton, &QPushButton::clicked, this, [&]() { startCountdown(RESTART_STRING); });
    connect(logoutButton, &QPushButton::clicked, this, [&]() { startCountdown(LOGOUT_STRING); });
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        if (shutdownButton->isChecked()) {
            shutdown();
        } else if (restartButton->isChecked()) {
            restart();
        } else if (logoutButton->isChecked()) {
            logout();
        }
    } else {
        cancelAction();
    }
}

void MainWindow::startCountdown(const QString &action) {
    actionType = action;
    label->setText(QString("%1 in: %2 seconds").arg(actionType).arg(countdown));
    label->show();
    timer->start(1000);
}

void MainWindow::updateCountdown() {
    if (countdown > 0) {
        countdown--;
        label->setText(QString("%1 in: %2 seconds").arg(actionType).arg(countdown));
    } else {
        timer->stop();
        if (actionType == SHUTDOWN_STRING) {
            shutdown();
        } else if (actionType == RESTART_STRING) {
            restart();
        } else if (actionType == LOGOUT_STRING) {
            logout();
        }
    }
}

void MainWindow::cancelAction() {
    timer->stop();
    countdown = 5;
    label->hide();
    shutdownButton->setChecked(false);
    restartButton->setChecked(false);
    logoutButton->setChecked(false);
}

void shutdown() {
    int ret = QProcess::execute("sudo", QStringList() << "systemctl" << "poweroff");
    if (ret != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to shutdown the system.");
    }
}

void restart() {
    int ret = QProcess::execute("sudo", QStringList() << "systemctl" << "reboot");
    if (ret != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to restart the system.");
    }
}

void logout() {
    int syncthingKillRet = QProcess::execute("killall", QStringList() << "syncthing");
    if (syncthingKillRet != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to kill syncthing process.");
    }

    int logoutRet = QProcess::execute("swaymsg", QStringList() << "exit");
    if (logoutRet != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to logout.");
    }
}