
// ObjectTrackingDlg.h : header file
//

/*
@ bref
CImageModel �� �̹��� �����͸� ����(cv::Mat)
CImageViewModel �� �̹��� �ε�, ���� �� ��ȯ(���, �÷�, HBITMAP ��ȯ)
CObjectTrackingDlg �� UI���� ViewModel�� ���� ������ ����
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
	CStatic m_pictureControl; // Picture Control �ڵ�
	HBITMAP m_hBitmap; // Bitmap �ڵ� ����
	void DrawImage(); // �̹��� ��� �Լ�
	void ReleaseBitmap(); // ���� Bitmap �޸� ����
	HBITMAP MatToHBITMAP(cv::Mat& matImage); // OpenCV Mat �� HBITMAP ��ȯ �Լ�

	
	void CreateBitmapInfo(int nWidth, int nHeight, int nBpp); // Bitmap ������ �����ϴ� �Լ�.
	void DrawImage(); // �׸��� �۾��� �����ϴ� �Լ�.

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
