#include "ImageModel.h"

CImageModel::CImageModel() : m_image(std::make_shared<cv::Mat>()) {}

void CImageModel::SetImage(const cv::Mat& image) {
    *m_image = image.clone();
}

std::shared_ptr<const cv::Mat> CImageModel::GetImage() const {
    return m_image;
}
