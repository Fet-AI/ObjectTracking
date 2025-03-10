#pragma once
#include "ImageModel.h"
#include <string>
#include <algorithm>

class CImageProcessor 
{
public:
    static bool ToReSize(std::shared_ptr<cv::Mat> image, std::string& errorMsg);
    static bool ToGray(std::shared_ptr<cv::Mat> image, std::string& errorMsg);
    static bool ToColor(std::shared_ptr<cv::Mat> image, std::string& errorMsg);
    bool ToBlur_Gaussian(const std::shared_ptr<cv::Mat> ori, std::shared_ptr<cv::Mat> dest, cv::Size size, int nStandardDeviation, cv::Rect roi, std::string& errorMsg);
};
