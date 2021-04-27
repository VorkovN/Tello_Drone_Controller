#ifndef TELLOWINDOW_H
#define TELLOWINDOW_H

#include "Drone.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TelloWindow; }
QT_END_NAMESPACE

class TelloWindow : public QMainWindow
{
    Q_OBJECT

public:
    TelloWindow(QWidget *parent = nullptr);
    ~TelloWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TelloWindow *ui;
};
#endif // TELLOWINDOW_H
