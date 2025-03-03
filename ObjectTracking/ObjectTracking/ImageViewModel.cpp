#include "ImageViewModel.h"

// 생성자
CImageViewModel::CImageViewModel() {}

// 이미지 로드
bool CImageViewModel::LoadImage(const std::string& filePath, std::string& errorMsg) 
{
    try 
    {
        cv::Mat image = cv::imread(filePath, cv::IMREAD_UNCHANGED);
        if (image.empty()) 
        {
            errorMsg = "Failed to load image: Empty or invalid file.";
            return false;
        }

        m_model.SetImage(image); // 🔹 Model에 이미지 저장
        return true;
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in LoadImage: " + std::string(e.what());
        return false;
    }
}

// 이미지 저장
bool CImageViewModel::SaveImage(const std::string& filePath, std::string& errorMsg) 
{
    try 
    {
        std::shared_ptr<const cv::Mat> image = m_model.GetImage();
        if (!image || image->empty()) 
        {
            errorMsg = "No image data to save.";
            return false;
        }

        if (!cv::imwrite(filePath, *image)) 
        {
            errorMsg = "Failed to save image.";
            return false;
        }
        return true;
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in SaveImage: " + std::string(e.what());
        return false;
    }
}

// 흑백 변환
void CImageViewModel::ConvertToGray(std::string& errorMsg) 
{
    std::shared_ptr<cv::Mat> image = std::const_pointer_cast<cv::Mat>(m_model.GetImage());
    if (CImageProcessor::ToGray(image, errorMsg)) 
    {
        // 변환 성공 -> UI 업데이트 가능
    }
}

// 컬러 변환
void CImageViewModel::ConvertToColor(std::string& errorMsg) 
{
    std::shared_ptr<cv::Mat> image = std::const_pointer_cast<cv::Mat>(m_model.GetImage());
    if (CImageProcessor::ToColor(image, errorMsg)) 
    {
        // 변환 성공 -> UI 업데이트 가능
    }
}

// Model 데이터 가져오기 (읽기 전용)
std::shared_ptr<const cv::Mat> CImageViewModel::GetImage() const 
{
    return m_model.GetImage();
}
