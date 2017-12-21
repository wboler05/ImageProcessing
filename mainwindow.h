#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include <QPointer>

#include "imagecontainer.h"
#include "improc.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void processInputImage();

protected slots:
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionExit_triggered();
    void resizeEvent(QResizeEvent * event);
    void on_kernel_size_sb_valueChanged(int);
    void on_std_dev_x_dsb_valueChanged(double);
    void on_std_dev_y_dsb_valueChanged(double);
    void on_swag_btn_pressed();

private:
    Ui::MainWindow *ui;
    QString m_save_file_name;
    QString m_open_file_name;

    size_t m_kernel_size = 3;
    double m_std_dev_x = 25;
    double m_std_dev_y = 5;

    void fixSizes();

};

#endif // MAINWINDOW_H
