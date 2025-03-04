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

    // 이미지 로드 및 저장
    bool LoadImage(const std::string& filePath, std::string& errorMsg);
    bool SaveImage(const std::string& filePath, std::string& errorMsg);

    // 이미지 변환 기능
    void ConvertToGray(std::string& errorMsg);
    void ConvertToColor(std::string& errorMsg);

    // Model 데이터 가져오기
    std::shared_ptr<const cv::Mat> GetImage() const;
    void SetImage(const cv::Mat& image);
};
