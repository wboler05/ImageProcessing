#ifndef IMAGECONTAINER_H
#define IMAGECONTAINER_H

#include <QImage>
#include <QPointer>
#include <QSharedPointer>

class ImageContainer
{
public:

    static ImageContainer * instance() {
        if (!m_instance) {
            m_instance = new ImageContainer();
        }
        return m_instance;
    }

    QSharedPointer<QImage> m_input_image;
    QSharedPointer<QImage> m_output_image;
    QSharedPointer<QImage> m_red_image;
    QSharedPointer<QImage> m_green_image;
    QSharedPointer<QImage> m_blue_image;

private:
    ImageContainer();

    static ImageContainer * m_instance;
};

#endif // IMAGECONTAINER_H
