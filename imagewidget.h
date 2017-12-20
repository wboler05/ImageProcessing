#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QOpenGLWidget>
#include <QWeakPointer>
#include <QImage>
#include <QPainter>
#include <QDebug>

class ImageWidget : public QOpenGLWidget
{
public:
    ImageWidget(QWidget * parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());

    void initializeGL(){}

    void paintGL() {
        QPainter painter(this);
        if (!m_image.isNull()) {
            painter.drawImage(QPoint(0,0), m_displayed_image);
        } else {
            painter.setBrush(QColor(27, 27, 27));
            painter.drawRect(rect());
        }
    }

    void resizeGL(int w, int h) {
        resizeImage();
    }

    void updateImage(const QImage & image) {
        m_image = image;
        resizeImage();
        update();
    }

private:
    QImage m_image;
    QImage m_displayed_image;

    void resizeImage() {
        if (!m_image.isNull()) {
            //qDebug() << "Size: " << size() << "\tImage: " << m_image.size();
            m_displayed_image = m_image.scaled(size(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
            //qDebug() << "Fucking image size: " << m_image.size();
        }
    }
};

#endif // IMAGEWIDGET_H
