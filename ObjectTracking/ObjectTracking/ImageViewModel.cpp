#include "ImageViewModel.h"

// ������
CImageViewModel::CImageViewModel() {}

// ��� ��ȯ (���� ó�� �߰�)
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
            // ��ȯ ���� -> UI ������Ʈ ����
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

// �÷� ��ȯ (���� ó�� �߰�)
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
            // ��ȯ ���� -> UI ������Ʈ ����
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
