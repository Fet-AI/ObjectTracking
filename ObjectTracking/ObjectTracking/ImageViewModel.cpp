#include "pch.h"
#include "ImageViewModel.h"
// Model�� �ε� ��û
bool CImageViewModel::LoadImage(const std::string& filePath, std::string& errorMsg) 
{
    return m_model.LoadImage(filePath, errorMsg); 
}

// Model�� ���� ��û
bool CImageViewModel::SaveImage(const std::string& filePath, std::string& errorMsg) 
{
    return m_model.SaveImage(filePath, errorMsg); 
}

// Model�� �̹��� �����͸� ����
cv::Mat CImageViewModel::GetImage() const 
{
    return m_model.m_image; 
}
