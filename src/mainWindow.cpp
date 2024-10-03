#include "mainWindow.h"
#include <QVBoxLayout>
#include <QProcess>
#include <QMessageBox>
#include <QKeyEvent>

#define SHUTDOWN_STRING "Shutdown"
#define RESTART_STRING "Restart"

void shutdown();
void restart();

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), countdown(2) {
    timer = new QTimer(this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    label = new QLabel(nullptr);
    label->hide();
    layout->addWidget(label);

    shutdownButton = new QPushButton(SHUTDOWN_STRING);
    restartButton = new QPushButton(RESTART_STRING);

    layout->addWidget(shutdownButton);
    layout->addWidget(restartButton);

    setLayout(layout);
    resize(400, 100);

    // Timer setup
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCountdown);

    // Connect button signals
    connect(shutdownButton, &QPushButton::clicked, this, [&]() { startCountdown(SHUTDOWN_STRING); });
    connect(restartButton, &QPushButton::clicked, this, [&]() { startCountdown(RESTART_STRING); });
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        if (shutdownButton->isChecked()) {
            shutdown();
        } else if (restartButton->isChecked()) {
            restart();
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
        }
    }
}

void MainWindow::cancelAction() {
    timer->stop();
    countdown = 2;
    label->setText("Action canceled.");
    label->hide();
    shutdownButton->setChecked(false);
    restartButton->setChecked(false);
}

void shutdown() {
    int ret = QProcess::execute("echo", QStringList() << SHUTDOWN_STRING);
    if (ret != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to shutdown the system.");
    }
}

void restart() {
    int ret = QProcess::execute("echo", QStringList() << RESTART_STRING);
    if (ret != 0) {
        QMessageBox::warning(nullptr, "Error", "Failed to restart the system.");
    }
}
