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
@ blurred: ���� ����� �̹���
@ cv::Size(5, 5): ����þ� Ŀ���� ũ�� (5x5)
@ 0: ����þ� Ŀ���� ǥ�� ���� (0�̸� �ڵ� ���)
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

        // ROI�� ��ȿ���� Ȯ��
        if (roi.width > 0 && roi.height > 0)
        {
            if (roi.x < 0 || roi.y < 0 ||
                roi.x + roi.width > image->cols ||
                roi.y + roi.height > image->rows)
            {
                errorMsg = "Invalid ROI: Out of image bounds.";
                return false;
            }

            // ROI ���� ����
            cv::Mat roiImage = (*image)(roi);

            // ROI�� ����þ� �� ����
            cv::GaussianBlur(roiImage, roiImage, size, nStandardDeviation);
        }
        else
        {
            // ��ü �̹����� ����þ� �� ����
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

