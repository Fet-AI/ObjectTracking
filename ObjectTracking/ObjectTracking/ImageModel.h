// ImageModel.h
/** 
* @brief
* - OpenCV Image Processing
* @detail
* - ����å���� ��Ģ(SRP) �ǰ�
* - ������ ������ ����
* - ����-��� ��Ģ(OCP) �ǰ�
* - Model�� �˰����� ������ �����ʰ�, Processor �� ó��
* @feat
* - CImageModel	SetImage(), GetImage()
*/
#pragma once
#include <opencv2/opencv.hpp>
#include <memory>

class CImageModel 
{
private:
    std::shared_ptr<cv::Mat> m_image; // OpenCV �̹��� ������ (private)

public:
    CImageModel(); // ������

    // �̹��� ����
    void SetImage(const cv::Mat& image);

    // ���� �̹��� �������� (�б� ����)
    std::shared_ptr<const cv::Mat> GetImage() const;
};
