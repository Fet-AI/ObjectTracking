#include "ImageProcessor.h"

/*
* @brief �÷�(BGR) �̹����� �׷��̽����Ϸ� ��ȯ
* @param image     ��ȯ�� �Է� �� ��� �̹��� (std::shared_ptr<cv::Mat>)
* @param errorMsg  ���� �߻� �� �޽��� ���� (std::string)
* @return ��ȯ ���� ���� (true: ����, false: ����)
* @details
*    - �Է� �̹����� ��� ������ ��ȯ���� �ʰ� ���� �޽����� ��ȯ
*    - OpenCV�� `cv::cvtColor`�� ����Ͽ� `cv::COLOR_BGR2GRAY` ��ȯ ����
*    - ���� �߻� �� `errorMsg`�� ���� �޽����� �����ϰ� false ��ȯ
*/
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

/*
* @brief �׷��̽����� �̹����� BGR �÷� �̹����� ��ȯ
* @param image     ��ȯ�� �Է� �� ��� �̹��� (std::shared_ptr<cv::Mat>)
* @param errorMsg  ���� �߻� �� �޽��� ���� (std::string)
* @return ��ȯ ���� ���� (true: ����, false: ����)
* @details
*    - �Է� �̹����� ��� ������ ��ȯ���� �ʰ� ���� �޽����� ��ȯ
*    - OpenCV�� `cv::cvtColor`�� ����Ͽ� `cv::COLOR_GRAY2BGR` ��ȯ ����
*    - ���� �߻� �� `errorMsg`�� ���� �޽����� �����ϰ� false ��ȯ
*/
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
* @brief ����þ� ���� �����Ͽ� ������ ����
* @param ori       �Է� ���� �̹��� (const std::shared_ptr<cv::Mat>)
* @param dest      ���� ����� ��� �̹��� (std::shared_ptr<cv::Mat>)
* @param size      ����þ� Ŀ�� ũ�� (��: cv::Size(5, 5))
* @param nStandardDeviation ����þ� Ŀ���� ǥ�� ���� (0�̸� �ڵ� ���)
* @param roi       ���� ������ ROI(Region of Interest), �⺻�� (0,0,0,0) �� ��ü �̹��� ó��
* @param errorMsg  ���� �߻� �� �޽��� ���� (std::string)
* @return �� ���� ���� ���� (true: ����, false: ����)
* @details
*    - `roi`�� ��ȿ�ϸ� �ش� �������� ���� �����ϰ�, ��ȿ���� ������ ��ü �̹����� �� ����
*    - `dest`�� nullptr�̸� `ori`�� �����Ͽ� ������ �� �� ����
*    - ���� �߻� �� `errorMsg`�� ���� �޽����� �����ϰ� false ��ȯ
*/
bool CImageProcessor::ToBlur_Gaussian(const std::shared_ptr<cv::Mat> ori, std::shared_ptr<cv::Mat> dest, cv::Size size, int nStandardDeviation, cv::Rect roi, std::string& errorMsg)
{
    try
    {
        if (!ori || ori->empty())
        {
            errorMsg = "Original image is empty. Cannot apply Gaussian blur.";
            return false;
        }

        // dest�� nullptr�̸� ���ο� Mat ����
        if (!dest)
        {
            dest = std::make_shared<cv::Mat>(ori->clone());
        }
        else
        {
            *dest = ori->clone();
        }

        // ROI�� ��ȿ���� Ȯ��
        if (roi.width > 0 && roi.height > 0)
        {
            if (roi.x < 0 
                || roi.y < 0 
                || roi.x + roi.width > ori->cols 
                || roi.y + roi.height > ori->rows)
            {
                errorMsg = "Invalid ROI: Out of image bounds.";
                return false;
            }

            // ROI ���� ����
            cv::Mat roiImage = (*dest)(roi);

            // ROI�� ����þ� �� ����
            cv::GaussianBlur((*ori)(roi), roiImage, size, nStandardDeviation);
        }
        else
        {
            // ��ü �̹����� ����þ� �� ����
            cv::GaussianBlur(*ori, *dest, size, nStandardDeviation);
        }

        return true;
    }
    catch (const std::exception& e)
    {
        errorMsg = "Exception in ToBlur_Gaussian: " + std::string(e.what());
        return false;
    }
}

