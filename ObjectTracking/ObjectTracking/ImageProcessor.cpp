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

/*
* bref 가우시안 블러 적용(노이즈 감소)
@ cv::GaussianBlur: 가우시안 필터를 사용하여 이미지에 블러를 적용
@ gray: 입력 그레이스케일 이미지
@ blurred: 블러가 적용된 이미지
@ cv::Size(5, 5): 가우시안 커널의 크기 (5x5)
@ 0: 가우시안 커널의 표준 편차 (0이면 자동 계산)
*/
bool CImageProcessor::ToBlur_Gaussian(std::shared_ptr<cv::Mat> image, cv::Mat gray, cv::Size size, int nStandardDeviation, std::string& errorMsg)
{
    return false;
}
