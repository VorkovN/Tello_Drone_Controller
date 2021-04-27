#include "tellowindow.h"
#include "./ui_tellowindow.h"

TelloWindow::TelloWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TelloWindow)
{
    ui->setupUi(this);
}

TelloWindow::~TelloWindow()
{
    delete ui;
}

void TelloWindow::on_pushButton_clicked()
{
    cv::Mat frame;
    std::thread([&](){
        while(true)
        {
            QImage *img = new QImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
            ui->label->repaint();
            ui->label->setPixmap(QPixmap::fromImage(*img));
//            ui->label->resize(img->width(),img->height());
//            imshow("TelloDriver video", frame);
//            std::cout << "FRAME: " << frame.cols << std::endl;

        }
    }).detach();


    Drone drone(&frame);
//    sleep(1);
//    drone.executeCommand("takeoff");
//    sleep(8);
//    drone.executeCommand("land");
    sleep(15);
}
