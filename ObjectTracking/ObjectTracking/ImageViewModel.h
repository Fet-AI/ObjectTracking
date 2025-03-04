#pragma once
#include "ImageModel.h"
#include "ImageProcessor.h"
#include <memory>
#include <Windows.h>

class CImageViewModel
{
private:
    CImageModel m_model; // Model ��ü

public:
    CImageViewModel(); // ������

    // �̹��� �ε� �� ����
    bool LoadImage(const std::string& filePath, std::string& errorMsg);
    bool SaveImage(const std::string& filePath, std::string& errorMsg);

    // �̹��� ��ȯ ���
    void ConvertToGray(std::string& errorMsg);
    void ConvertToColor(std::string& errorMsg);

    // Model ������ ��������
    std::shared_ptr<const cv::Mat> GetImage() const;
    void SetImage(const cv::Mat& image);
};
