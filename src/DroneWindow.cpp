#include "DroneWindow.h"


DroneWindow::DroneWindow(QWidget *parent)
    : QWidget(parent), _rect(QApplication::desktop()->screenGeometry())
{
    //создание кнопки выход
    _quitBtn = new QPushButton("Finish the flight", this);
    _quitBtn->setGeometry(0.8 * _rect.width(), 0.85 * _rect.height(), 0.15 * _rect.width(), 0.075 * _rect.height());
    connect(_quitBtn, &QPushButton::clicked, this, &DroneWindow::onQuitButtonClicked);

    //создание пространства под видео
    _frameLabel = new QLabel(this);
    _frameLabel->setGeometry(0, 0, 0.75 * _rect.width(), _rect.height());

    _statusLabel = new QLabel(this);
    _statusLabel->setGeometry(0.775 * _rect.width(), 0.02 * _rect.height(), 0.2 * _rect.width(), 0.35 * _rect.height());

    _helpLabel = new QLabel(this);
    _helpLabel->setGeometry(0.775 * _rect.width(), 0.38 * _rect.height(), 0.2 * _rect.width(), 0.35 * _rect.height());
    _helpLabel->setText("Help\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp\nHelp");

    _statusTimerId = startTimer(constants::STATUS_DELAY);
    _videoTimerId = startTimer(constants::VIDEO_FRAME_DELAY);

    std::cout << "Window has been created" << std::endl;
}

void DroneWindow::timerEvent(QTimerEvent *e)
{

    if (e->timerId() == _videoTimerId)
        updateVideoFrame();

    if (e->timerId() == _statusTimerId)
        updateStatus();
}

void DroneWindow::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    std::cout << key << std::endl;

    if (key == Qt::Key_Shift)
        _drone.executeCommand("takeoff");

    else if (key == Qt::Key_Control)
        _drone.executeCommand("land");

    else if (key == Qt::Key_PageUp)
        _drone.executeCommand("up 20");

    else if (key == Qt::Key_PageDown)
        _drone.executeCommand("down 20");

    else if (key == Qt::Key_W)
        _drone.executeCommand("forward 20");

    else if (key == Qt::Key_S)
        _drone.executeCommand("back 20");

    else if (key == Qt::Key_A)
        _drone.executeCommand("left 20");

    else if (key == Qt::Key_D)
        _drone.executeCommand("rigth 20");

    else if (key == Qt::Key_Comma)
        _drone.executeCommand("ccw 15");

    else if (key == Qt::Key_Period)
        _drone.executeCommand("cw 15");


    QWidget::keyPressEvent(e);
}

void DroneWindow::onQuitButtonClicked()
{
    //todo добавить логику по экстренному приземлению
    qApp->quit();
    std::cout << "quitBtn" << std::endl;
}

void DroneWindow::updateVideoFrame()
{
    _frame = _drone.returnVideoFrame();
    _img = QImage(_frame.data, _frame.cols, _frame.rows, QImage::Format_BGR888);
    _frameLabel->setPixmap(QPixmap::fromImage(_img).scaled(0.75 * _rect.width(), _rect.height()));
    repaint();
}
void DroneWindow::updateStatus()
{
    _statusLabel->setText(_drone.returnStatus());
    repaint();
}

DroneWindow::~DroneWindow()
{
    killTimer(_statusTimerId);
    killTimer(_statusTimerId);
    std::cout << "DroneWindow Destructor" << std::endl;
}

