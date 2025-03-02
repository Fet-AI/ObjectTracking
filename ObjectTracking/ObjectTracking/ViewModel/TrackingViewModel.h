#pragma once

#include "./Model/TrackingDataModel.h"
#include <memory>

class TrackingViewModel
{
private:
    std::shared_ptr<TrackingDataModel> model;  // Model�� ���� (������ ����)

public:
    // �����ڿ��� Model�� ���Թ޵��� ����
    TrackingViewModel(std::shared_ptr<TrackingDataModel> dataModel)
        : model(dataModel) 
    {}

    // ���� ������ & ���� ���� ������ ����
    TrackingViewModel& operator=(const TrackingViewModel&) = delete;
    TrackingViewModel(const TrackingViewModel&) = delete;

    // �̹��� �ε�
    bool LoadImage(const std::string& filePath)
    {
        if (!model) return false;

        cv::Mat image = cv::imread(filePath);
        if (image.empty()) return false;

        model->SetImage(image);  // Model�� ���� �������� �ʰ� �Լ� ȣ��
        model->SetFileName(filePath);
        return true;
    }

    // �̹��� ����
    bool SaveImage(const std::string& filePath)
    {
        if (!model || model->GetImage().empty()) return false;

        return cv::imwrite(filePath, model->GetImage());
    }

    // �̹��� ��ȯ
    const cv::Mat& GetImage() const
    {
        return model->GetImage();
    }
};
