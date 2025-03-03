#include "ImageProcessor.h"

bool CImageProcessor::ToGray(std::shared_ptr<cv::Mat> image, std::string& errorMsg) 
{
    try 
    {
        if (!image || image->empty()) 
        {
            errorMsg = "Image is empty. Cannot convert to grayscale.";
            return false;
        }
        cv::cvtColor(*image, *image, cv::COLOR_BGR2GRAY);
        return true;
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in ToGray: " + std::string(e.what());
        return false;
    }
}

bool CImageProcessor::ToColor(std::shared_ptr<cv::Mat> image, std::string& errorMsg) 
{
    try 
    {
        if (!image || image->empty()) 
        {
            errorMsg = "Image is empty. Cannot convert to color.";
            return false;
        }
        cv::cvtColor(*image, *image, cv::COLOR_GRAY2BGR);
        return true;
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in ToColor: " + std::string(e.what());
        return false;
    }
}
