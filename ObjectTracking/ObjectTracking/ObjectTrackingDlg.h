#pragma once
#include "ImageLibrary.h"
#include "TrackingViewModel.h" // ViewModel 추가

// CObjectTrackingDlg dialog
class CObjectTrackingDlg : public CDialogEx
{
    // Construction
public:
    CObjectTrackingDlg(CWnd* pParent = nullptr); // standard constructor

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_OBJECTTRACKING_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

public:
    HICON m_hIcon{};
    BITMAP m_pBitmapInfo{};
    TrackingViewModel viewModel; // ViewModel 추가
    CImage m_image{};

    void CreateBitmapInfo(int nWidth, int nHeight, int nBpp); // Bitmap 정보를 생성하는 함수.
    void DrawImage(); // 그리는 작업을 수행하는 함수.

    // Implementation
protected:
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
    afx_msg void OnBnClickedBtnImgLoad();
    afx_msg void OnBnClickedBtnImgSave();
    afx_msg void OnDestroy();
};
