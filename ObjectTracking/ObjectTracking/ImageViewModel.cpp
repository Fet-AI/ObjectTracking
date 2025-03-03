#include "ImageViewModel.h"

// 생성자
CImageViewModel::CImageViewModel() {}

// 흑백 변환 (예외 처리 추가)
void CImageViewModel::ConvertToGray(std::string& errorMsg) 
{
    try 
    {
        auto image = std::const_pointer_cast<cv::Mat>(m_model.GetImage());
        if (!image || image->empty()) 
        {
            errorMsg = "Error: Image is empty or not loaded.";
            return;
        }

        if (CImageProcessor::ToGray(image, errorMsg)) 
        {
            // 변환 성공 -> UI 업데이트 가능
        }
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in ConvertToGray: " + std::string(e.what());
    }
    catch (...) 
    {
        errorMsg = "Unknown error occurred in ConvertToGray.";
    }
}

// 컬러 변환 (예외 처리 추가)
void CImageViewModel::ConvertToColor(std::string& errorMsg) {
    try 
    {
        auto image = std::const_pointer_cast<cv::Mat>(m_model.GetImage());

        if (!image || image->empty()) 
        {
            errorMsg = "Error: Image is empty or not loaded.";
            return;
        }
        if (CImageProcessor::ToColor(image, errorMsg)) 
        {
            // 변환 성공 -> UI 업데이트 가능
        }
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in ConvertToColor: " + std::string(e.what());
    }
    catch (...) 
    {
        errorMsg = "Unknown error occurred in ConvertToColor.";
    }
}
