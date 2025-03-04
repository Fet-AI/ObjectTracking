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

        SetImage(image); // 🔹 Model에 이미지 저장 및 UI 갱신
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

    if (!image || image->empty())
    {
        errorMsg = "Error: No image loaded!";
        return;
    }

    if (image->channels() == 3) // 컬러 이미지인 경우만 변환
    {
        cv::Mat grayImage;
        cv::cvtColor(*image, grayImage, cv::COLOR_BGR2GRAY);

        //  Model에 변환된 흑백 이미지 저장
        SetImage(grayImage);
    }
    else
    {
        errorMsg = "Image is already grayscale!";
    }
}

// 컬러 변환 (추가 구현)
void CImageViewModel::ConvertToColor(std::string& errorMsg)
{
    std::shared_ptr<cv::Mat> image = std::const_pointer_cast<cv::Mat>(m_model.GetImage());

    if (!image || image->empty())
    {
        errorMsg = "Error: No image loaded!";
        return;
    }

    if (image->channels() == 1) // 흑백 이미지만 컬러 변환 가능
    {
        cv::Mat colorImage;
        cv::cvtColor(*image, colorImage, cv::COLOR_GRAY2BGR);

        // 변환된 컬러 이미지를 Model에 저장
        SetImage(colorImage);
    }
    else
    {
        errorMsg = "Image is already in color!";
    }
}

// Model 데이터 가져오기 (읽기 전용)
std::shared_ptr<const cv::Mat> CImageViewModel::GetImage() const
{
    auto image = m_model.GetImage();
    if (!image)
    {
        return std::make_shared<cv::Mat>(); // 빈 이미지 반환하여 nullptr 방지
    }
    return image;
}

// 이미지 설정 (Model 업데이트 및 UI 갱신)
void CImageViewModel::SetImage(const cv::Mat& image)
{
    m_model.SetImage(image);  // Model에 이미지 저장
}
