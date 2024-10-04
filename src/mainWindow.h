#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QPushButton *shutdownButton;
    QPushButton *restartButton;
    QPushButton *logoutButton;
    void startCountdown(const QString &action);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void updateCountdown();
    void cancelAction();

    QString actionType;
    int countdown;
    QTimer *timer;
    QLabel *label;
    
};

#endif // MAINWINDOW_H
