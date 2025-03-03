#pragma once
#include "ImageModel.h"
#include <string>

class CImageViewModel {
private:
    CImageModel m_model; // Model을 포함하여 UI와 분리

public:
    // 이미지 로드 요청 (View → ViewModel → Model)
    bool LoadImage(const std::string& filePath, std::string& errorMsg);

    // 이미지 저장 요청 (View → ViewModel → Model)
    bool SaveImage(const std::string& filePath, std::string& errorMsg);

    // Model의 이미지 데이터 가져오기 (View에서 직접 Model을 접근하지 않도록 함)
    cv::Mat GetImage() const;
};
