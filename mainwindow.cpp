#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fixSizes();
    ui->kernel_size_sb->setValue(m_kernel_size);
    ui->std_dev_x_dsb->setValue(m_std_dev_x);
    ui->std_dev_y_dsb->setValue(m_std_dev_y);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered() {
    if (!ImageContainer::instance()->m_output_image) {
        qWarning() << "Output image has not been created yet.";
        return;
    }

    QDir curDir = qApp->applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this, "Save output image to file.", curDir.absolutePath(), "Images (*.png *.jpg *.gif)");

    QFile file(fileName);
    if (!file.open(QFile::Truncate)) {
        qWarning() << "Failed to open file for saving.";
        return;
    }
    m_save_file_name = fileName;

    if (ImageContainer::instance()->m_output_image->save(fileName)) {
        qDebug() << "File save successful: " << m_save_file_name;
    } else {
        qWarning() << "Unable to save file: " << m_save_file_name;
    }

}

void MainWindow::on_actionLoad_triggered() {
    QDir curDir = qApp->applicationDirPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open output image", curDir.absolutePath(), "Image File (*.png *.jpg *.gif)");

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << "Failed to open file for saving.";
        return;
    }
    m_open_file_name = fileName;

    ImageContainer::instance()->m_input_image = QSharedPointer<QImage>(new QImage(fileName));
    if (ImageContainer::instance()->m_input_image->isNull()) {
        qWarning() << "Failed to open file: " << fileName;
    } else {
        qDebug() << "Successfully opened file: " << fileName;
        putSomeSwagOnThem();
    }

}

void MainWindow::on_actionExit_triggered() {
    exit(1);
}

void MainWindow::putSomeSwagOnThem() {
    if (ImageContainer::instance()->m_input_image.isNull()) return;

    QImage inputImage = *ImageContainer::instance()->m_input_image.data();
    QImage redImage = inputImage;
    QImage greenImage = inputImage;
    QImage blueImage = inputImage;

    for (size_t i = 0; i < inputImage.size().width(); i++) {
        for (size_t j = 0; j < inputImage.size().height(); j++) {
            QColor inputColor = inputImage.pixelColor(i, j);
            QColor redColor = inputColor, greenColor = inputColor, blueColor = inputColor;
            redColor.setBlue(0);redColor.setGreen(0);
            greenColor.setRed(0);greenColor.setBlue(0);
            blueColor.setRed(0);blueColor.setGreen(0);

            redImage.setPixelColor(i, j, redColor);
            greenImage.setPixelColor(i, j, greenColor);
            blueImage.setPixelColor(i, j, blueColor);
        }
    }

    QImage outputImage;
    //ImProc::gaussian(inputImage, outputImage, 3, 5, 5);
    ImProc::DoG(inputImage, outputImage, m_kernel_size, m_std_dev_x, m_std_dev_y);
    //ImProc::DoG(inputImage, outputImage, 5, 25, 5, 25, 5);
    QImage grayScale;
    //ImProc::grayscale(inputImage, grayScale);
    //ImProc::gaussian(grayScale, outputImage, 3, 1, 1);
    //ImProc::DoG(grayScale, outputImage, 7, 0.5, 0.5);

    ImageContainer::instance()->m_red_image = QSharedPointer<QImage>(new QImage(redImage));
    ImageContainer::instance()->m_green_image = QSharedPointer<QImage>(new QImage(greenImage));
    ImageContainer::instance()->m_blue_image = QSharedPointer<QImage>(new QImage(blueImage));
    ImageContainer::instance()->m_output_image = QSharedPointer<QImage>(new QImage(outputImage));

    ui->input_ogl->updateImage(inputImage);
    ui->red_ogl->updateImage(redImage);
    ui->green_ogl->updateImage(greenImage);
    ui->blue_ogl->updateImage(blueImage);
    ui->output_ogl->updateImage(outputImage);




}

void MainWindow::resizeEvent(QResizeEvent * event) {
    fixSizes();
}

void MainWindow::fixSizes() {
    //ui->red_ogl->resize(ui->red_gb->size());
    //ui->green_ogl->resize(ui->green_gb->size());
    //ui->blue_ogl->resize(ui->blue_gb->size());
    //ui->input_ogl->resize(ui->input_gb->size());
    //ui->output_ogl->resize(ui->output_gb->size());

}

void MainWindow::on_kernel_size_sb_valueChanged(int v) {
    m_kernel_size = ui->kernel_size_sb->value();
}

void MainWindow::on_std_dev_x_dsb_valueChanged(double v) {
    m_std_dev_x = ui->std_dev_x_dsb->value();
}

void MainWindow::on_std_dev_y_dsb_valueChanged(double v) {
    m_std_dev_y = ui->std_dev_y_dsb->value();
}

void MainWindow::on_swag_btn_pressed() {
    putSomeSwagOnThem();
}
