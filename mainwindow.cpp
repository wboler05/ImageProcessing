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
    QString fileName = QFileDialog::getOpenFileName(this, "Open input image", curDir.absolutePath(), "Image File (*.png *.jpg *.gif);;All Files (*.*)");

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
        processInputImage();
    }

}

void MainWindow::on_actionExit_triggered() {
    exit(1);
}

void MainWindow::processInputImage() {
    if (ImageContainer::instance()->m_input_image.isNull()) return;

    CustomImage inputImage = *ImageContainer::instance()->m_input_image.data();
    QImage redImage(inputImage.size(), inputImage.format());
    QImage greenImage(inputImage.size(), inputImage.format());
    QImage blueImage(inputImage.size(), inputImage.format());
    redImage.fill(QColor(0,0,0));
    greenImage.fill(QColor(0,0,0));
    blueImage.fill(QColor(0,0,0));

    for (size_t i = 0; i < inputImage.size().width(); i++) {
        for (size_t j = 0; j < inputImage.size().height(); j++) {
            QColor redColor, greenColor, blueColor;
            redColor.setRedF(inputImage.data()[i][j][0]);
            greenColor.setGreenF(inputImage.data()[i][j][1]);
            blueColor.setBlueF(inputImage.data()[i][j][2]);

            redImage.setPixelColor(i, j, redColor);
            greenImage.setPixelColor(i, j, greenColor);
            blueImage.setPixelColor(i, j, blueColor);
        }
    }

    CustomImage outputImage;
    CustomImage grayScale;
    CustomImage normalImage;
    ImProc::normalizeImage(inputImage, outputImage);
    //ImProc::grayscale(normalImage, grayScale);
    //ImProc::gaussian(normalImage, outputImage, m_kernel_size, m_std_dev_x, m_std_dev_y);
    //ImProc::DoG(grayScale, outputImage, m_kernel_size, m_std_dev_x, m_std_dev_y);

    ImageContainer::instance()->m_red_image = QSharedPointer<QImage>(new QImage(redImage));
    ImageContainer::instance()->m_green_image = QSharedPointer<QImage>(new QImage(greenImage));
    ImageContainer::instance()->m_blue_image = QSharedPointer<QImage>(new QImage(blueImage));
    ImageContainer::instance()->m_output_image = QSharedPointer<QImage>(new QImage(outputImage.imageTransfer()));

    ui->input_ogl->updateImage(inputImage.imageTransfer());
    ui->red_ogl->updateImage(redImage);
    ui->green_ogl->updateImage(greenImage);
    ui->blue_ogl->updateImage(blueImage);
    ui->output_ogl->updateImage(outputImage.imageTransfer());




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
    processInputImage();
}
