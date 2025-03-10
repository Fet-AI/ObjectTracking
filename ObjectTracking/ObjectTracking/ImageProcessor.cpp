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
* bref ����þ� �� ����(������ ����)
@ cv::GaussianBlur: ����þ� ���͸� ����Ͽ� �̹����� ���� ����
@ gray: �Է� �׷��̽����� �̹���
@ blurred: ���� ����� �̹���
@ cv::Size(5, 5): ����þ� Ŀ���� ũ�� (5x5)
@ 0: ����þ� Ŀ���� ǥ�� ���� (0�̸� �ڵ� ���)
*/
bool CImageProcessor::ToBlur_Gaussian(std::shared_ptr<cv::Mat> image, cv::Mat gray, cv::Size size, int nStandardDeviation, std::string& errorMsg)
{
    return false;
}
