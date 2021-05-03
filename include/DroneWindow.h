#pragma once

#include <thread>

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRect>
#include <QKeyEvent>
#include <QThread>

#include "Drone.h"

class DroneWindow: public QWidget
{
public:
    explicit DroneWindow(QWidget *parent = nullptr);
    ~DroneWindow() override;

private slots:
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void onQuitButtonClicked();
    void updateVideoFrame();
    void updateStatus();

private:
    bool _isVideoAlive;

    std::stringstream _buffer{};
    std::streambuf *_cout_buf;

    QRect _rect;
    QImage _img;
    QLabel *_frameLabel;
    QLabel *_statusLabel;
    QLabel *_logLabel;
    QPushButton *_quitBtn;
    std::thread _videoThread;

    cv::Mat _frame;
//    int _videoTimerId;
    int _statusTimerId;
    int _readyTakeCommandId;
    bool _readyTakeCommand;

    int _upCounter = 0;
    int _downCounter = 0;
    int _forwardCounter = 0;
    int _backCounter = 0;
    int _leftCounter = 0;
    int _rigthCounter = 0;
    int _ccwCounter = 0;
    int _cwCounter = 0;

    Drone _drone;

};