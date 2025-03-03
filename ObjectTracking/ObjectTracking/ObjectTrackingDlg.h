
// ObjectTrackingDlg.h : header file
//

/*
@ bref
CImageModel → 이미지 데이터를 보관(cv::Mat)
CImageViewModel → 이미지 로드, 저장 및 변환(흑백, 컬러, HBITMAP 변환)
CObjectTrackingDlg → UI에서 ViewModel을 통해 데이터 조작
*/

#pragma once
#include "ImageLibrary.h"
#include "ImageViewModel.h"

// CObjectTrackingDlg dialog
class CObjectTrackingDlg : public CDialogEx
{
// Construction
public:
	CObjectTrackingDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTRACKING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
private:
	CImageViewModel m_viewModel{};
	CStatic m_pictureControl; // Picture Control 핸들
	HBITMAP m_hBitmap; // Bitmap 핸들 저장
	void DrawImage(); // 이미지 출력 함수
	void ReleaseBitmap(); // 기존 Bitmap 메모리 해제
	HBITMAP MatToHBITMAP(cv::Mat& matImage); // OpenCV Mat → HBITMAP 변환 함수

	
	void CreateBitmapInfo(int nWidth, int nHeight, int nBpp); // Bitmap 정보를 생성하는 함수.
	void DrawImage(); // 그리는 작업을 수행하는 함수.

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
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
