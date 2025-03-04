// ImageModel.h
/** 
* @brief
* - OpenCV Image Processing
* @detail
* - 단일책임의 원칙(SRP) 의거
* - 데이터 보관만 진행
* - 개방-폐쇄 원칙(OCP) 의거
* - Model이 알고리즘을 가지고 있지않고, Processor 가 처리
* @feat
* - CImageModel	SetImage(), GetImage()
*/
#pragma once
#include <opencv2/opencv.hpp>
#include <memory>

class CImageModel 
{
private:
    std::shared_ptr<cv::Mat> m_image; // OpenCV 이미지 데이터 (private)

public:
    CImageModel(); // 생성자

    // 이미지 설정
    void SetImage(const cv::Mat& image);

    // 현재 이미지 가져오기 (읽기 전용)
    std::shared_ptr<const cv::Mat> GetImage() const;
};
