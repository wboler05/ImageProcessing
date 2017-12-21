#include "improc.h"

bool ImProc::gaussian(
        CustomImage & src,
        CustomImage & dst,
        const size_t & k_size,
        const double & std_dev_x,
        const double & std_dev_y) {

    size_t k_size_ = odifyK(k_size);
    std::vector<std::vector<double>> kernel = gaussianKernel(k_size_, std_dev_x, std_dev_y);
    normalizeKernel(kernel);
    return convolve(src, dst, kernel);
}

/**
 * @brief ImProc::convolve
 * @param src
 * @param dst
 * @param kernel
 * @todo Convert to faster byte operations
 * @return
 */
bool ImProc::convolve(CustomImage & src, CustomImage & dst, std::vector<std::vector<double>> & kernel) {

    QImage dst_img(src.size(), src.format());
    dst_img.fill(QColor(0,0,0,0));
    dst = CustomImage(dst_img);

    QSize imageSize(src.size());

    int k = (int)kernel.size();
    int halfK = kernel.size() / 2;

    for (int x = 0; x < imageSize.width(); x++) {
        for (int y = 0; y < imageSize.height(); y++) {
            for (int i = 0; i < k; i++) {
                int shifted_x = x + (halfK - i);
                //int shifted_i = k-(i+halfK)-1;
                if (shifted_x < 0 || shifted_x >= imageSize.width()) {
                    continue;
                }

                for (int j = 0; j < k; j++) {

                    int shifted_y = y + (halfK - j);
                    //int shifted_j = k-(j+halfK)-1;
                    if (shifted_y < 0 || shifted_y >= imageSize.height()) {
                        continue;
                    }

                    for (size_t k = 0; k < 3; k++ ) {
                        dst.data()[x][y][k] = src.data()[shifted_x][shifted_y][k] * kernel[i][j];
                    }
                    /*

                    QColor pixel_at_dst = dst.pixelColor(x, y);
                    QColor pixel_at_src = src.pixelColor(shifted_x,shifted_y);

                    double redPixel = pixel_at_dst.redF() + pixel_at_src.redF() * kernel[i][j];
                    double greenPixel = pixel_at_dst.greenF() + pixel_at_src.greenF() * kernel[i][j];
                    double bluePixel = pixel_at_dst.blueF() + pixel_at_src.blueF() * kernel[i][j];

                    redPixel = fmax(redPixel, 0);
                    greenPixel = fmax(greenPixel, 0);
                    bluePixel = fmax(bluePixel, 0);

                    redPixel = fmin(redPixel, 1.0);
                    greenPixel = fmin(greenPixel, 1.0);
                    bluePixel = fmin(bluePixel, 1.0);

                    pixel_at_dst.setRedF(redPixel);
                    pixel_at_dst.setGreenF(greenPixel);
                    pixel_at_dst.setBlueF(bluePixel);

                    dst.setPixelColor(x, y, pixel_at_dst);
                    */
                }
            }
        }
    }
    return true;
}

std::vector<std::vector<double>> ImProc::gaussianKernel(
        const size_t & k_size,
        const double & std_dev_x,
        const double & std_dev_y)
{
    size_t k_size_ = odifyK(k_size);

    std::vector<std::vector<double>> kernel(k_size_);
    for (size_t i = 0; i < kernel.size(); i++) {
        kernel[i].resize(k_size_, 0);
    }

    double sum = 0;

    double halfK = floor(k_size_ / 2);
    double shifted_i = -halfK;
    double shifted_j = -halfK;
    for (size_t i = 0; i < k_size_; i++) {
        for (size_t j = 0; j < k_size_; j++) {
            kernel[i][j] =
                gaussianFormula(shifted_i + (double)i, std_dev_x) *
                gaussianFormula(shifted_j + (double)j, std_dev_y);
            //sum += kernel[i][j];
        }
    }

    //normalizeKernel(kernel);
    /*
    for (size_t i = 0; i < k_size_; i++) {
        for(size_t j = 0; j < k_size_; j++) {
            kernel[i][j] /= sum;
        }
    }
    */

    return kernel;
}

double ImProc::gaussianFormula(const double & x, const double & std_dev) {
    double g = 1 / (sqrt(2.0*M_PI)*std_dev);
    g *= exp(-pow(x / (2*std_dev), 2));
    return g;
}

bool ImProc::DoG(
        CustomImage & src, CustomImage & dst,
        const size_t & k_size, const double & upper_std_dev, const double & lower_std_dev) {
    return DoG(src, dst, k_size, upper_std_dev, lower_std_dev, upper_std_dev, lower_std_dev);
}

bool ImProc::DoG(
        CustomImage & src, CustomImage & dst,
        const size_t &k_size, const double & upper_std_dev_x, const double & lower_std_dev_x,
        const double & upper_std_dev_y, const double & lower_std_dev_y)
{
    CustomImage dst1, dst2, dst3;

    size_t k_size_ = odifyK(k_size);

    std::vector<std::vector<double>> upperKernel = gaussianKernel(k_size_, upper_std_dev_x, upper_std_dev_y);
    std::vector<std::vector<double>> lowerKernel = gaussianKernel(k_size_, lower_std_dev_x, lower_std_dev_y);

    //normalizeKernel(upperKernel);
    //normalizeKernel(lowerKernel);

//    gaussian(src, dst1, k_size, upper_std_dev_x, upper_std_dev_y);
//    gaussian(src, dst2, k_size, lower_std_dev_x, lower_std_dev_y);

    normalizeKernel(upperKernel);
    normalizeKernel(lowerKernel);

    for (size_t i = 0; i < upperKernel.size(); i++) {
        for (size_t j = 0; j < upperKernel[i].size(); j++) {
            upperKernel[i][j] -= lowerKernel[i][j];
        }
    }

    normalizeKernel(upperKernel);

    convolve(src, dst, upperKernel);
    //convolve(src, dst2, lowerKernel);

    //subtractImage(dst3, dst1, dst2);

    //normalizeImage(dst, dst1);

    /*

    for (size_t i = 0; i < k_size_; i++) {
        for (size_t j = 0; j < k_size_; j++) {
            upperKernel[i][j] -= lowerKernel[i][j];
        }
    }
    */

    //normalizeKernel(upperKernel);

    //return convolve(src, dst, upperKernel);
    return true;
}

size_t ImProc::odifyK(const size_t & k) {
    return k % 2 == 0 ? k+1 : k;
}

void ImProc::normalizeKernel(std::vector<std::vector<double>> & kernel) {
    double sum = 0;
    double max = -std::numeric_limits<double>::max();
    double min = std::numeric_limits<double>::max();
    for (size_t i = 0; i < kernel.size(); i++) {
        for (size_t j = 0; j < kernel[i].size(); j++) {
            min = fmin(min, kernel[i][j]);
        }
    }

    if (min < 0) {
        for (size_t i = 0; i < kernel.size(); i++) {
            for (size_t j = 0; j < kernel[i].size(); j++) {
                kernel[i][j] += min;
            }
        }
    }

    for (size_t i = 0; i < kernel.size(); i++) {
        for(size_t j = 0; j < kernel[i].size(); j++) {
            sum += kernel[i][j];
        }
    }

    for (size_t i = 0; i < kernel.size(); i++) {
        for(size_t j = 0; j < kernel[i].size(); j++) {
            kernel[i][j] /= sum;
        }
    }
}

void ImProc::grayscale(CustomImage & src, CustomImage & dst) {
    QSize imageSize = src.size();

    QImage dst_img(imageSize, src.format());
    dst_img.fill(QColor(0,0,0));
    dst = CustomImage(dst_img);

    //dst = QImage(imageSize, src.format());
    //dst.fill(QColor(0,0,0));

    for (int i = 0; i < imageSize.width(); i++) {
        for (int j = 0; j < imageSize.height(); j++) {
            //QColor color = src.pixelColor(i, j);
            //double red = 0.299 * color.redF();
            //double green = 0.587 * color.greenF();
            //double blue = 0.114 * color.blueF();
            //double Y = (red+green+blue)*255.0;

            double red = 0.299 * src.data()[i][j][0];
            double green = 0.587 * src.data()[i][j][1];
            double blue = 0.114 * src.data()[i][j][2];
            double Y = (red+green+blue)*255.0;

            //QColor newColor(Y, Y, Y);
            //dst.setPixelColor(i, j, newColor);
            for (int k = 0; k < 3; k++) {
                dst.data()[i][j][k] = Y;
            }
        }
    }
}

void ImProc::normalizeImage(CustomImage & src, CustomImage & dst) {

    dst = CustomImage(QImage(src.size(), src.format()));

    std::vector<double> min, max;
    min.resize(3,  std::numeric_limits<double>::max());
    max.resize(3, -std::numeric_limits<double>::max());

    QSize imageSize = src.size();
    for (int x = 0; x < imageSize.width(); x++) {
        for (int y = 0; y < imageSize.height(); y++) {
            for (int k = 0; k < 3; k++) {
                min[k] = fmin(min[k], src.data()[x][y][k]);
                max[k] = fmax(max[k], src.data()[x][y][k]);
            }
            /*
            QColor pixel = src.pixelColor(x, y);
            min[0] = fmin(min[0], pixel.redF());
            min[1] = fmin(min[1], pixel.greenF());
            min[2] = fmin(min[2], pixel.blueF());

            max[0] = fmax(max[0], pixel.redF());
            max[1] = fmax(max[1], pixel.greenF());
            max[2] = fmax(max[2], pixel.blueF());
            */
        }
    }

    for (int x = 0; x < imageSize.width(); x++) {
        for (int y = 0; y < imageSize.height(); y++) {
            for (int k = 0; k < 3; k++) {
                dst.data()[x][y][k] = (src.data()[x][y][k] - min[k]) / (max[k]-min[k]);
            }

            /*
            QColor pixel = src.pixelColor(x, y);

            double red = (pixel.redF() - min[0]) / (max[0]-min[0]);
            double green = (pixel.greenF() - min[1]) / (max[1]-min[1]);
            double blue = (pixel.blueF() - min[2]) / (max[2]-min[2]);

            pixel.setRedF(red);
            pixel.setGreenF(green);
            pixel.setBlueF(blue);

            dst.setPixelColor(x, y, pixel);
            */
        }
    }
}

bool ImProc::subtractImage(CustomImage & dst, CustomImage & im1, CustomImage & im2) {
    if (im1.size() != im2.size()) {
        qWarning() << "Failed to subtract images: size does not match."
                << "im1: " << im1.size() << " != im2: " << im2.size();
        return false;
    }

    if (im1.format() != im2.format()) {
        qWarning() << "Failed to subtract images: format does not match."
                      << "im1: " << im1.format() << " != im2: " << im2.format();
        return false;
    }

    dst = CustomImage(QImage(im1.size(), im1.format()));

    QSize imageSize = im1.size();
    for (int i = 0; i < imageSize.width(); i++) {
        for (int j = 0; j < imageSize.height(); j++) {
            for (int k = 0; k < 3; k++) {
                dst.data()[i][j][k] = im1.data()[i][j][k] - im2.data()[i][j][k];
            }
            /*
            QColor imageColor1 = im1.pixelColor(i, j);
            QColor imageColor2 = im2.pixelColor(i, j);

            int red1 = imageColor1.red();
            int green1 = imageColor1.green();
            int blue1 = imageColor1.blue();

            int red2 = imageColor2.red();
            int green2 = imageColor2.green();
            int blue2 = imageColor2.blue();


            double newRed = imageColor1.redF() - imageColor2.redF();
            double newGreen = imageColor1.greenF() - imageColor2.greenF();
            double newBlue = imageColor1.blueF() - imageColor2.blueF();

            newRed = fmin(newRed, 1.0);
            newGreen = fmin(newGreen, 1.0);
            newBlue = fmin(newBlue, 1.0);

            newRed = fmax(newRed, 0.0);
            newGreen = fmax(newGreen, 0.0);
            newBlue = fmax(newBlue, 0.0);

            imageColor1.setRedF(newRed);
            imageColor1.setGreenF(newGreen);
            imageColor1.setBlueF(newBlue);

            dst.setPixelColor(i, j, imageColor1);
            */
        }
    }
}
