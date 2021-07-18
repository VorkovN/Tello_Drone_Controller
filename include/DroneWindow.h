#pragma once

#include <thread>

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRect>
#include <QKeyEvent>
#include <QTextEdit>
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
    bool _isVideoThreadAlive;
    bool _isStatusThreadAlive;

    std::stringstream _buffer{};
    std::streambuf *_cout_buf;

    QRect _rect;
    QImage _img;
    QLabel *_frameLabel;
    QLabel *_statusLabel;
    QTextEdit* _logTextEdit;
    QPushButton *_quitBtn;
    std::thread _videoThread;
    std::thread _statusThread;

    cv::Mat _frame;
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
    std::map<Qt::Key, std::string> _commandMap;

};