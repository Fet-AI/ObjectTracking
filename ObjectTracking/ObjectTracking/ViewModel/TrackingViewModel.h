#pragma once

#include "./Model/TrackingDataModel.h"
#include <memory>

class TrackingViewModel
{
private:
    std::shared_ptr<TrackingDataModel> model;  // Model을 참조 (느슨한 결합)

public:
    // 생성자에서 Model을 주입받도록 변경
    TrackingViewModel(std::shared_ptr<TrackingDataModel> dataModel)
        : model(dataModel) 
    {}

    // 복사 생성자 & 복사 대입 연산자 삭제
    TrackingViewModel& operator=(const TrackingViewModel&) = delete;
    TrackingViewModel(const TrackingViewModel&) = delete;

    // 이미지 로드
    bool LoadImage(const std::string& filePath)
    {
        if (!model) return false;

        cv::Mat image = cv::imread(filePath);
        if (image.empty()) return false;

        model->SetImage(image);  // Model을 직접 수정하지 않고 함수 호출
        model->SetFileName(filePath);
        return true;
    }

    // 이미지 저장
    bool SaveImage(const std::string& filePath)
    {
        if (!model || model->GetImage().empty()) return false;

        return cv::imwrite(filePath, model->GetImage());
    }

    // 이미지 반환
    const cv::Mat& GetImage() const
    {
        return model->GetImage();
    }
};
