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
@ blurred: 블러가 적용된 이미지
@ cv::Size(5, 5): 가우시안 커널의 크기 (5x5)
@ 0: 가우시안 커널의 표준 편차 (0이면 자동 계산)
*/
bool CImageProcessor::ToBlur_Gaussian(std::shared_ptr<cv::Mat> image, cv::Size size, int nStandardDeviation, cv::Rect roi, std::string& errorMsg)
{
    try
    {
        if (!image || image->empty())
        {
            errorMsg = "Image is empty. Cannot apply Gaussian blur.";
            return false;
        }

        // ROI가 유효한지 확인
        if (roi.width > 0 && roi.height > 0)
        {
            if (roi.x < 0 || roi.y < 0 ||
                roi.x + roi.width > image->cols ||
                roi.y + roi.height > image->rows)
            {
                errorMsg = "Invalid ROI: Out of image bounds.";
                return false;
            }

            // ROI 영역 선택
            cv::Mat roiImage = (*image)(roi);

            // ROI에 가우시안 블러 적용
            cv::GaussianBlur(roiImage, roiImage, size, nStandardDeviation);
        }
        else
        {
            // 전체 이미지에 가우시안 블러 적용
            cv::GaussianBlur(*image, *image, size, nStandardDeviation);
        }

        return true;
    }
    catch (const std::exception& e)
    {
        errorMsg = "Exception in ToBlur_Gaussian: " + std::string(e.what());
        return false;
    }
}

