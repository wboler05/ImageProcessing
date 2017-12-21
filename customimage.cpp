#include "customimage.h"

CustomImage::CustomImage()
{
}

CustomImage::~CustomImage() {

}

CustomImage::CustomImage(const CustomImage & l) :
    m_image(l.m_image),
    m_image_vec(l.m_image_vec),
    m_modified(l.m_modified)
{

}

CustomImage::CustomImage(CustomImage && r) :
    m_image(std::move(r.m_image)),
    m_image_vec(std::move(r.m_image_vec)),
    m_modified(std::move(r.m_modified))
{

}

CustomImage & CustomImage::operator= (const CustomImage & l) {
    m_image = l.m_image;
    m_image_vec = l.m_image_vec;
    m_modified = l.m_modified;
    return *this;
}

CustomImage & CustomImage::operator= (CustomImage && r) {
    m_image = std::move(r.m_image);
    m_image_vec = std::move(r.m_image_vec);
    m_modified = std::move(r.m_modified);
    return *this;
}

CustomImage::CustomImage(const QImage & li) {
    m_image = li;
    updateVectorFromImage();
}

CustomImage::CustomImage(QImage && ri) {
    m_image = std::move(ri);
    updateVectorFromImage();
}

CustomImage::CustomImage(const ImageVector & lv) :
    m_image_vec(lv),
    m_modified(true)
{
}

CustomImage::CustomImage(ImageVector && rv)  :
    m_image_vec(std::move(rv)),
    m_modified(true)
{

}

void CustomImage::setImage(const QImage & li) {
    m_image = li;
    updateVectorFromImage();
}

void CustomImage::setImage(QImage && ri) {
    m_image = std::move(ri);
    updateVectorFromImage();
}

void CustomImage::setSize(const QSize & s) {
    m_image_vec.resize(s.width());
    for (size_t i = 0; i < m_image_vec.size(); i++) {
        m_image_vec[i].resize(s.height());
        for (size_t j = 0; j < m_image_vec[i].size(); j++) {
            m_image_vec[i][j].resize(4, 0.0);
        }
    }
}

void CustomImage::updateImageFromVector() {
    if (m_image_vec.size() == 0) return;
    if (m_image_vec[0].size() == 0) return;

    m_image = QImage(QSize(m_image_vec.size(), m_image_vec[0].size()), m_image.format());

    for (size_t i = 0; i < m_image_vec.size(); i++) {
        for (size_t j = 0; j < m_image_vec[i].size(); j++) {
            double red, blue, green, alpha;
            red = m_image_vec[i][j][0];
            green = m_image_vec[i][j][1];
            blue = m_image_vec[i][j][2];
            alpha = m_image_vec[i][j][3];

            red = fmin(red, 1.0);
            green = fmin(green, 1.0);
            blue = fmin(blue, 1.0);
            alpha = fmin(alpha, 1.0);

            red = fmax(red, 0);
            green = fmax(green, 0);
            blue = fmax(blue, 0);
            alpha = fmax(alpha, 0);

            QColor pixelColor;
            pixelColor.setRedF(red);
            pixelColor.setGreenF(green);
            pixelColor.setBlueF(blue);
            pixelColor.setAlphaF(alpha);

            m_image.setPixelColor(i, j, pixelColor);
        }
    }
}

void CustomImage::updateVectorFromImage() {
    setSize(m_image.size());
    QSize imageSize = m_image.size();
    for (size_t i = 0; i < m_image_vec.size(); i++) {
        for (size_t j = 0; j < m_image_vec[i].size(); j++) {
            QColor pixel = m_image.pixelColor(i, j);
            m_image_vec[i][j][0] = pixel.redF();
            m_image_vec[i][j][1] = pixel.greenF();
            m_image_vec[i][j][2] = pixel.blueF();
            m_image_vec[i][j][3] = pixel.alphaF();
        }
    }
    m_modified = false;
}
