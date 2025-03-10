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
    bool CImageProcessor::ToBlur_Gaussian(std::shared_ptr<cv::Mat> image, cv::Size size, int nStandardDeviation, cv::Rect roi, std::string& errorMsg);
};
