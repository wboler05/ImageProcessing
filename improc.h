#ifndef IMPROC_H
#define IMPROC_H

#include <vector>
#include <QImage>

class ImProc
{
public:

    static bool gaussian(QImage & src, QImage & dst, const size_t &k_size, const double & std_dev_x=1.0, const double & std_dev_y=1.0);
    static bool convolve(QImage & src, QImage & dst, std::vector<std::vector<double>> & kernel);
    static std::vector<std::vector<double>> gaussianKernel(const size_t & k_size=3, const double & std_dev_x=1.0, const double & std_dev_y=1.0);
    static double gaussianFormula(const double & x, const double & std_dev);

    static bool DoG(QImage & src, QImage & dst, const size_t &k_size, const double & upper_std_dev_x, const double & lower_std_dev_x, const double & upper_std_dev_y, const double & lower_std_dev_y);
    static bool DoG(QImage & src, QImage & dst, const size_t & k_size, const double & upper_std_dev, const double & lower_std_dev);

    static size_t odifyK(const size_t & k);

    static void normalizeKernel(std::vector<std::vector<double>> & kernel);

    static void grayscale(QImage & src, QImage & dst);

private:
    ImProc()=delete;
};

#endif // IMPROC_H
