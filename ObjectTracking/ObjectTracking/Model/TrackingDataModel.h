#pragma once

#include <opencv2/opencv.hpp>
#include <string>

class TrackingDataModel
{
private:
    cv::Mat m_matImage;
    std::string m_strFileName;

public:
    void SetImage(const cv::Mat& image) { m_matImage = image.clone(); }
    const cv::Mat& GetImage() const { return m_matImage; }

    void SetFileName(const std::string& fileName) { m_strFileName = fileName; }
    const std::string& GetFileName() const { return m_strFileName; }
};
