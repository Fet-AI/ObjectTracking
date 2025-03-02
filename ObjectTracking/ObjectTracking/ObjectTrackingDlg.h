#pragma once
#include "ImageLibrary.h"
#include "TrackingViewModel.h" // ViewModel �߰�

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
    TrackingViewModel viewModel; // ViewModel �߰�
    CImage m_image{};

    void CreateBitmapInfo(int nWidth, int nHeight, int nBpp); // Bitmap ������ �����ϴ� �Լ�.
    void DrawImage(); // �׸��� �۾��� �����ϴ� �Լ�.

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
