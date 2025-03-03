#pragma once
#include "ImageModel.h"
#include <string>

class CImageProcessor 
{
public:
    static bool ToGray(std::shared_ptr<cv::Mat> image, std::string& errorMsg);
    static bool ToColor(std::shared_ptr<cv::Mat> image, std::string& errorMsg);
};
