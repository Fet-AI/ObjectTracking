// ImageModel.h
#pragma once

/**
* @feat
* OpenCV Image Processing
*/

#include <opencv2/opencv.hpp>
#include <exception>
#include <string>

class CImageModel 
{
public:
    cv::Mat m_image; // OpenCV �̹��� ������ ����

    // �̹��� �ε�: ���� ��ο��� OpenCV Mat ��ü�� ��ȯ
    bool LoadImage(const std::string& filePath, std::string& errorMsg);

    // �̹��� ����: OpenCV Mat ��ü�� ���Ϸ� ����
    bool SaveImage(const std::string& filePath, std::string& errorMsg);
};