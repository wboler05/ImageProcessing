#ifndef IMPROC_H
#define IMPROC_H

#include <vector>
#include <QDebug>

#include <customimage.h>

class ImProc
{
public:

    static bool gaussian(CustomImage & src, CustomImage & dst, const size_t &k_size, const double & std_dev_x=1.0, const double & std_dev_y=1.0);
    static bool convolve(CustomImage & src, CustomImage & dst, std::vector<std::vector<double>> & kernel);
    static std::vector<std::vector<double>> gaussianKernel(const size_t & k_size=3, const double & std_dev_x=1.0, const double & std_dev_y=1.0);
    static double gaussianFormula(const double & x, const double & std_dev);

    static bool DoG(CustomImage & src, CustomImage & dst, const size_t &k_size, const double & upper_std_dev_x, const double & lower_std_dev_x, const double & upper_std_dev_y, const double & lower_std_dev_y);
    static bool DoG(CustomImage & src, CustomImage & dst, const size_t & k_size, const double & upper_std_dev, const double & lower_std_dev);

    static size_t odifyK(const size_t & k);

    static void normalizeKernel(std::vector<std::vector<double>> & kernel);

    static void grayscale(CustomImage & src, CustomImage & dst);

    static bool subtractImage(CustomImage & dst, CustomImage & im1, CustomImage & im2);

    static void normalizeImage(CustomImage & src, CustomImage & dst);

private:
    ImProc()=delete;
};

#endif // IMPROC_H
