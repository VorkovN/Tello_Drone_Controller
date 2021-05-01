#pragma once

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRect>

#include "Drone.h"

class DroneWindow: public QWidget
{
public:
    explicit DroneWindow(QWidget *parent = nullptr);
    ~DroneWindow() override;

private slots:
    void timerEvent(QTimerEvent *) override;
    void onStartVideoButtonClick();
    void onStopVideoButtonClick();
    void updateVideoFrame();
    void updateStatus();

private:
    QRect _rect;//параметры экрана
    QLabel *_frameLabel;
    QLabel *_statusLabel;
    QLabel *_helpLabel;
    QPushButton *_startBtn;
    QPushButton *_stopBtn;
    QPushButton *_quitBtn;
    int _videoTimerId;
    int _statusTimerId;

    Drone _drone;

};