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

    // �̹��� ��ȯ ���
    void ConvertToGray(std::string& errorMsg);
    void ConvertToColor(std::string& errorMsg);
};
