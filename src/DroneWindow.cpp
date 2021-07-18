#include "DroneWindow.h"


DroneWindow::DroneWindow(QWidget *parent)
    : _cout_buf(std::cout.rdbuf()), QWidget(parent), _rect(QApplication::desktop()->screenGeometry())
{
    _commandMap = { { Qt::Key_Shift, "takeoff" },
                    { Qt::Key_Control, "land" },
                    { Qt::Key_PageUp, "up " },
                    { Qt::Key_PageDown, "down " },
                    { Qt::Key_W, "forward " },
                    { Qt::Key_S, "back " },
                    { Qt::Key_A, "left " },
                    { Qt::Key_D, "right " },
                    { Qt::Key_Comma, "ccw " },
                    { Qt::Key_Period, "cw " }};


    std::cout.rdbuf(_buffer.rdbuf());
    //создание кнопки выход
    _quitBtn = new QPushButton("Finish the flight", this);
    _quitBtn->setGeometry(0.8 * _rect.width(), 0.85 * _rect.height(), 0.15 * _rect.width(), 0.075 * _rect.height());
    connect(_quitBtn, &QPushButton::clicked, this, &DroneWindow::onQuitButtonClicked);

    //создание пространства под видео
    _frameLabel = new QLabel(this);
    _frameLabel->setGeometry(0, 0, 0.75 * _rect.width(), _rect.height());

    _statusLabel = new QLabel(this);
    _statusLabel->setGeometry(0.775 * _rect.width(), 0.02 * _rect.height(), 0.2 * _rect.width(), 0.35 * _rect.height());

    _logTextEdit = new QTextEdit(this);
    _logTextEdit->setGeometry(0.775 * _rect.width(), 0.38 * _rect.height(), 0.2 * _rect.width(), 0.35 * _rect.height());

    _readyTakeCommandId = startTimer(constants::READY_TAKE_COMMAND_DELAY);

    _isVideoThreadAlive = true;
    _videoThread = std::thread(&DroneWindow::updateVideoFrame, this);
    _videoThread.detach();

    _isStatusThreadAlive = true;
    _statusThread = std::thread(&DroneWindow::updateStatus, this);
    _statusThread.detach();

    std::cout << "Window has been created" << std::endl;
}

void DroneWindow::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == _readyTakeCommandId)
        _readyTakeCommand = true;
}

void DroneWindow::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    std::cout << key << std::endl;

//    if (key == Qt::Key_Shift && _readyTakeCommand) {
//        _readyTakeCommand = false;
//        _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]);
//    }
//    else if (key == Qt::Key_Control && _readyTakeCommand) {
//        _readyTakeCommand = false;
//        _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]);
//    }
//
//    else if (key == Qt::Key_PageUp){
//        _upCounter += (_upCounter == 0) ? 20 : 1;
//        if (_readyTakeCommand){
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_upCounter));
//            _upCounter = 0;
//        }
//    }
//
//
//    else if (key == Qt::Key_PageDown) {
//        _downCounter += (_downCounter == 0) ? 20 : 1;
//        if (_readyTakeCommand) {
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_downCounter));
//            _downCounter = 0;
//        }
//    }
//
//    else if (key == Qt::Key_W){
//        _forwardCounter += (_forwardCounter == 0) ? 20 : 1;
//        if (_readyTakeCommand) {
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_forwardCounter));
//            _forwardCounter = 0;
//        }
//    }
//
//    else if (key == Qt::Key_S){
//        _backCounter += (_backCounter == 0) ? 20 : 1;
//        if (_readyTakeCommand) {
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_backCounter));
//            _backCounter = 0;
//        }
//    }
//
//    else if (key == Qt::Key_A){
//        _leftCounter += (_leftCounter == 0) ? 20 : 1;
//        if (_readyTakeCommand) {
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_leftCounter));
//            _leftCounter = 0;
//        }
//    }
//
//    else if (key == Qt::Key_D){
//        _rigthCounter += (_rigthCounter == 0) ? 20 : 1;
//        if (_readyTakeCommand) {
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_rigthCounter));
//            _rigthCounter = 0;
//        }
//    }
//
//    else if (key == Qt::Key_Comma){
//        _ccwCounter += 5;
//        if (_readyTakeCommand) {
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_ccwCounter));
//            _ccwCounter = 0;
//        }
//    }
//
//    else if (key == Qt::Key_Period){
//        _cwCounter += 5;
//        if (_readyTakeCommand) {
//            _readyTakeCommand = false;
//            _drone.executeCommand(_commandMap[static_cast<Qt::Key>(e->key())]  + " "  + std::to_string(_cwCounter));
//            _cwCounter = 0;
//        }
//    }


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
    while(_isVideoThreadAlive)
    {
		std::this_thread::sleep_for(std::chrono::milliseconds(constants::VIDEO_FRAME_DELAY));
        _frame = _drone.returnVideoFrame();
        _img = QImage(_frame.data, _frame.cols, _frame.rows, QImage::Format_BGR888);
        _frameLabel->setPixmap(QPixmap::fromImage(_img).scaled(0.75 * _rect.width(), _rect.height()));
    }
}

void DroneWindow::updateStatus()
{
    while (_isStatusThreadAlive)
    {
		std::this_thread::sleep_for(std::chrono::milliseconds(constants::STATUS_DELAY));
        _statusLabel->setText(_drone.returnStatus());
        _logTextEdit->setText(_buffer.str().c_str());
    }
}

DroneWindow::~DroneWindow()
{
    _isVideoThreadAlive = false;
    _isStatusThreadAlive = false;
    std::cout << "DroneWindow Destructor" << std::endl;

    std::cout.rdbuf(_cout_buf);
    _cout_buf = nullptr;
}

