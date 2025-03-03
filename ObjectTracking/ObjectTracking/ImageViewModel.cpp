#include "pch.h"
#include "ImageViewModel.h"
// Model에 로드 요청
bool CImageViewModel::LoadImage(const std::string& filePath, std::string& errorMsg) 
{
    return m_model.LoadImage(filePath, errorMsg); 
}

// Model에 저장 요청
bool CImageViewModel::SaveImage(const std::string& filePath, std::string& errorMsg) 
{
    return m_model.SaveImage(filePath, errorMsg); 
}

// Model의 이미지 데이터를 제공
cv::Mat CImageViewModel::GetImage() const 
{
    return m_model.m_image; 
}
