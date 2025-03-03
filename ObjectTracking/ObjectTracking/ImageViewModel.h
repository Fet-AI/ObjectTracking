#pragma once
#include "ImageModel.h"
#include "ImageProcessor.h"
#include <memory>
#include <Windows.h>

class CImageViewModel 
{
private:
    CImageModel m_model; // Model 객체

public:
    CImageViewModel(); // 생성자

    // 이미지 변환 기능
    void ConvertToGray(std::string& errorMsg);
    void ConvertToColor(std::string& errorMsg);
};
