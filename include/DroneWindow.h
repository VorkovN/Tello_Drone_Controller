#pragma once

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRect>
#include <QKeyEvent>

#include "Drone.h"

class DroneWindow: public QWidget
{
public:
    explicit DroneWindow(QWidget *parent = nullptr);
    ~DroneWindow() override;

private slots:
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e);
    void onQuitButtonClicked();
    void updateVideoFrame();
    void updateStatus();

private:
    QRect _rect;
    QImage _img;
    QLabel *_frameLabel;
    QLabel *_statusLabel;
    QLabel *_helpLabel;
    QPushButton *_quitBtn;


    cv::Mat _frame;
    int _videoTimerId;
    int _statusTimerId;

    Drone _drone;

};