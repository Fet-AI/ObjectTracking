#include "pch.h"
#include "ImageModel.h"

bool CImageModel::LoadImage(const std::string& filePath, std::string& errorMsg) 
{
    try 
    {
        m_image = cv::imread(filePath, cv::IMREAD_COLOR);
        if (m_image.empty()) 
        {
            errorMsg = "Failed to load image: Empty image.";
            return false;
        }
        return true;
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in LoadImage: " + std::string(e.what());
        return false;
    }
}

bool CImageModel::SaveImage(const std::string& filePath, std::string& errorMsg) 
{
    try 
    {
        if (m_image.empty()) 
        {
            errorMsg = "No image data to save.";
            return false;
        }
        if (!cv::imwrite(filePath, m_image)) 
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
