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
    cv::Mat m_image; // OpenCV 이미지 데이터 저장

    // 이미지 로드: 파일 경로에서 OpenCV Mat 객체로 변환
    bool LoadImage(const std::string& filePath, std::string& errorMsg);

    // 이미지 저장: OpenCV Mat 객체를 파일로 저장
    bool SaveImage(const std::string& filePath, std::string& errorMsg);
};