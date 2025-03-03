#pragma once
#include "ImageModel.h"
#include <string>

class CImageViewModel {
private:
    CImageModel m_model; // Model�� �����Ͽ� UI�� �и�

public:
    // �̹��� �ε� ��û (View �� ViewModel �� Model)
    bool LoadImage(const std::string& filePath, std::string& errorMsg);

    // �̹��� ���� ��û (View �� ViewModel �� Model)
    bool SaveImage(const std::string& filePath, std::string& errorMsg);

    // Model�� �̹��� ������ �������� (View���� ���� Model�� �������� �ʵ��� ��)
    cv::Mat GetImage() const;
};
