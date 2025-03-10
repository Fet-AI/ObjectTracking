#include "ImageProcessor.h"

/*
* @brief 컬러(BGR) 이미지를 그레이스케일로 변환
* @param image     변환할 입력 및 출력 이미지 (std::shared_ptr<cv::Mat>)
* @param errorMsg  오류 발생 시 메시지 저장 (std::string)
* @return 변환 성공 여부 (true: 성공, false: 실패)
* @details
*    - 입력 이미지가 비어 있으면 변환하지 않고 오류 메시지를 반환
*    - OpenCV의 `cv::cvtColor`를 사용하여 `cv::COLOR_BGR2GRAY` 변환 수행
*    - 예외 발생 시 `errorMsg`에 오류 메시지를 저장하고 false 반환
*/
bool CImageProcessor::ToGray(std::shared_ptr<cv::Mat> image, std::string& errorMsg) 
{
    try 
    {
        if (!image || image->empty()) 
        {
            errorMsg = "Image is empty. Cannot convert to grayscale.";
            return false;
        }
        cv::cvtColor(*image, *image, cv::COLOR_BGR2GRAY);
        return true;
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in ToGray: " + std::string(e.what());
        return false;
    }
}

/*
* @brief 그레이스케일 이미지를 BGR 컬러 이미지로 변환
* @param image     변환할 입력 및 출력 이미지 (std::shared_ptr<cv::Mat>)
* @param errorMsg  오류 발생 시 메시지 저장 (std::string)
* @return 변환 성공 여부 (true: 성공, false: 실패)
* @details
*    - 입력 이미지가 비어 있으면 변환하지 않고 오류 메시지를 반환
*    - OpenCV의 `cv::cvtColor`를 사용하여 `cv::COLOR_GRAY2BGR` 변환 수행
*    - 예외 발생 시 `errorMsg`에 오류 메시지를 저장하고 false 반환
*/
bool CImageProcessor::ToColor(std::shared_ptr<cv::Mat> image, std::string& errorMsg) 
{
    try 
    {
        if (!image || image->empty()) 
        {
            errorMsg = "Image is empty. Cannot convert to color.";
            return false;
        }
        cv::cvtColor(*image, *image, cv::COLOR_GRAY2BGR);
        return true;
    }
    catch (const std::exception& e) 
    {
        errorMsg = "Exception in ToColor: " + std::string(e.what());
        return false;
    }
}

/*
* @brief 가우시안 블러를 적용하여 노이즈 감소
* @param ori       입력 원본 이미지 (const std::shared_ptr<cv::Mat>)
* @param dest      블러가 적용된 출력 이미지 (std::shared_ptr<cv::Mat>)
* @param size      가우시안 커널 크기 (예: cv::Size(5, 5))
* @param nStandardDeviation 가우시안 커널의 표준 편차 (0이면 자동 계산)
* @param roi       블러를 적용할 ROI(Region of Interest), 기본값 (0,0,0,0) → 전체 이미지 처리
* @param errorMsg  오류 발생 시 메시지 저장 (std::string)
* @return 블러 적용 성공 여부 (true: 성공, false: 실패)
* @details
*    - `roi`가 유효하면 해당 영역에만 블러를 적용하고, 유효하지 않으면 전체 이미지에 블러 적용
*    - `dest`가 nullptr이면 `ori`를 복사하여 저장한 후 블러 적용
*    - 예외 발생 시 `errorMsg`에 오류 메시지를 저장하고 false 반환
*/
bool CImageProcessor::ToBlur_Gaussian(const std::shared_ptr<cv::Mat> ori, std::shared_ptr<cv::Mat> dest, cv::Size size, int nStandardDeviation, cv::Rect roi, std::string& errorMsg)
{
    try
    {
        if (!ori || ori->empty())
        {
            errorMsg = "Original image is empty. Cannot apply Gaussian blur.";
            return false;
        }

        // dest가 nullptr이면 새로운 Mat 생성
        if (!dest)
        {
            dest = std::make_shared<cv::Mat>(ori->clone());
        }
        else
        {
            *dest = ori->clone();
        }

        // ROI가 유효한지 확인
        if (roi.width > 0 && roi.height > 0)
        {
            if (roi.x < 0 
                || roi.y < 0 
                || roi.x + roi.width > ori->cols 
                || roi.y + roi.height > ori->rows)
            {
                errorMsg = "Invalid ROI: Out of image bounds.";
                return false;
            }

            // ROI 영역 선택
            cv::Mat roiImage = (*dest)(roi);

            // ROI에 가우시안 블러 적용
            cv::GaussianBlur((*ori)(roi), roiImage, size, nStandardDeviation);
        }
        else
        {
            // 전체 이미지에 가우시안 블러 적용
            cv::GaussianBlur(*ori, *dest, size, nStandardDeviation);
        }

        return true;
    }
    catch (const std::exception& e)
    {
        errorMsg = "Exception in ToBlur_Gaussian: " + std::string(e.what());
        return false;
    }
}

