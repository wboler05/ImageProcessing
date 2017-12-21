#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H

#include <QImage>
#include <vector>

class CustomImage
{
    //      x           y           Channel     pixel_val{0 to 1}
    typedef std::vector<std::vector<std::vector<double>>> ImageVector;

public:
    CustomImage();
    ~CustomImage();
    CustomImage(const CustomImage &);
    CustomImage(CustomImage &&);
    CustomImage & operator= (const CustomImage &);
    CustomImage & operator= (CustomImage &&);

    CustomImage(const QImage &);
    CustomImage(QImage &&);
    CustomImage(const ImageVector &);
    CustomImage(ImageVector &&);

    void setImage(const QImage &);
    void setImage(QImage &&);

    ImageVector & data() {
        m_modified = true;
        return m_image_vec;
    }

    const QImage & imageTransfer() {
        if (m_modified) {
            updateImageFromVector();
        }
        return m_image;
    }

    QSize size() const { return m_image.size(); }
    void setSize(const QSize & s);
    QImage::Format format() const { return m_image.format(); }

private:
    QImage m_image;
    ImageVector m_image_vec;

    bool m_modified=true;

    void updateVectorFromImage();
    void updateImageFromVector();
};

#endif // CUSTOMIMAGE_H
