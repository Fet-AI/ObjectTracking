#pragma once
#include "ImageModel.h"
#include <string>
#include <algorithm>

class CImageProcessor 
{
public:
    static bool ToGray(std::shared_ptr<cv::Mat> image, std::string& errorMsg);
    static bool ToColor(std::shared_ptr<cv::Mat> image, std::string& errorMsg);
    static bool ToBlur_Gaussian(std::shared_ptr<cv::Mat> image,cv::Mat gray, cv::Size size,int nStandardDeviation ,std::string& errorMsg);
};
