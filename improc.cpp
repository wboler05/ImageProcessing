#include "improc.h"

bool ImProc::gaussian(
        QImage & src,
        QImage & dst,
        const size_t & k_size,
        const double & std_dev_x,
        const double & std_dev_y) {

    size_t k_size_ = odifyK(k_size);
    std::vector<std::vector<double>> kernel = gaussianKernel(k_size_, std_dev_x, std_dev_y);
    normalizeKernel(kernel);
    return convolve(src, dst, kernel);
}

bool ImProc::convolve(QImage & src, QImage & dst, std::vector<std::vector<double>> & kernel) {

    dst = QImage(src.size(), src.format());
    dst.fill(QColor(0,0,0,0));

    QSize imageSize(src.size());

    int k = (int)kernel.size();
    int halfK = kernel.size() / 2;

    for (int x = 0; x < imageSize.width(); x++) {
        for (int y = 0; y < imageSize.height(); y++) {
            for (int i = -halfK; i <= halfK; i++) {
                int shifted_x = x + i;
                int shifted_i = k-(i+halfK)-1;
                if (shifted_x < 0 || shifted_x >= imageSize.width()) {
                    continue;
                }

                for (int j = -halfK; j <= halfK; j++) {

                    int shifted_y = y + j;
                    int shifted_j = k-(j+halfK)-1;
                    if (shifted_y < 0 || shifted_y >= imageSize.height()) {
                        continue;
                    }

                    QColor pixel_at_dst = dst.pixelColor(x, y);
                    QColor pixel_at_src = src.pixelColor(shifted_x,shifted_y);

                    double redPixel = pixel_at_dst.redF() + pixel_at_src.redF() * kernel[shifted_i][shifted_j];
                    double greenPixel = pixel_at_dst.greenF() + pixel_at_src.greenF() * kernel[shifted_i][shifted_j];
                    double bluePixel = pixel_at_dst.blueF() + pixel_at_src.blueF() * kernel[shifted_i][shifted_j];

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
        QImage & src, QImage & dst,
        const size_t & k_size, const double & upper_std_dev, const double & lower_std_dev) {
    return DoG(src, dst, k_size, upper_std_dev, lower_std_dev, upper_std_dev, lower_std_dev);
}

bool ImProc::DoG(
        QImage & src, QImage & dst,
        const size_t &k_size, const double & upper_std_dev_x, const double & lower_std_dev_x,
        const double & upper_std_dev_y, const double & lower_std_dev_y)
{
    size_t k_size_ = odifyK(k_size);

    std::vector<std::vector<double>> upperKernel = gaussianKernel(k_size_, upper_std_dev_x, upper_std_dev_y);
    std::vector<std::vector<double>> lowerKernel = gaussianKernel(k_size_, lower_std_dev_x, lower_std_dev_y);

    for (size_t i = 0; i < k_size_; i++) {
        for (size_t j = 0; j < k_size_; j++) {
            upperKernel[i][j] -= lowerKernel[i][j];
        }
    }

    normalizeKernel(upperKernel);

    return convolve(src, dst, upperKernel);
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

void ImProc::grayscale(QImage & src, QImage & dst) {
    QSize imageSize = src.size();

    dst = QImage(imageSize, src.format());
    dst.fill(QColor(0,0,0));

    for (int i = 0; i < imageSize.width(); i++) {
        for (int j = 0; j < imageSize.height(); j++) {
            QColor color = src.pixelColor(i, j);
            double red = 0.299 * color.redF();
            double green = 0.587 * color.greenF();
            double blue = 0.114 * color.blueF();
            double Y = (red+green+blue)*255.0;

            QColor newColor(Y, Y, Y);
            dst.setPixelColor(i, j, newColor);
        }
    }
}
