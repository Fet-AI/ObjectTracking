#include "pch.h"
#include "framework.h"
#include "ObjectTracking.h"
#include "ObjectTrackingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CObjectTrackingDlg::CObjectTrackingDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OBJECTTRACKING_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    // ViewModel을 스마트 포인터로 생성하고 Model을 주입
    auto model = std::make_shared<TrackingDataModel>();
    viewModel = std::make_shared<TrackingViewModel>(model);
}

void CObjectTrackingDlg::OnBnClickedBtnImgLoad()
{
    CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY,
        _T("Image Files (*.jpg;*.bmp;*.png)|*.jpg;*.bmp;*.png|All Files (*.*)|*.*||"));

    if (fileDlg.DoModal() == IDOK)
    {
        CString path = fileDlg.GetPathName();
        std::string strPath(CT2CA(path));

        if (viewModel->LoadImage(strPath)) // 포인터로 접근
        {
            DrawImage();
        }
        else
        {
            AfxMessageBox(_T("이미지를 불러올 수 없습니다."));
        }
    }
}

void CObjectTrackingDlg::OnBnClickedBtnImgSave()
{
    if (viewModel->GetImage().empty())
    {
        AfxMessageBox(_T("저장할 이미지가 없습니다."));
        return;
    }

    CFileDialog fileDlg(FALSE, _T("jpg"), NULL,
        OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
        _T("Image Files (*.jpg;*.bmp;*.png)|*.jpg;*.bmp;*.png|All Files (*.*)|*.*||"));

    if (fileDlg.DoModal() == IDOK)
    {
        CString path = fileDlg.GetPathName();
        std::string strPath(CT2CA(path));

        if (viewModel->SaveImage(strPath)) // 포인터로 접근
        {
            AfxMessageBox(_T("이미지를 저장했습니다."));
        }
        else
        {
            AfxMessageBox(_T("이미지를 저장할 수 없습니다."));
        }
    }
}
