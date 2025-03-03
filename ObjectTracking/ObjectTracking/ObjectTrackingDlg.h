// ObjectTrackingDlg.h : header file
//

/*
@brief
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

	// Private members
private:
	CImageViewModel m_viewModel{}; // ViewModel ��ü
	CStatic m_pictureControl; // Picture Control �ڵ�
	HBITMAP m_hBitmap; // Bitmap �ڵ� ����
	BITMAPINFO* m_pBitmapInfo = nullptr; // Bitmap ������ �����ϴ� ������

	// Image ���� �Լ�
	void DrawImage(); // �̹��� ��� �Լ�
	void ReleaseBitmap(); // ���� Bitmap �޸� ����
	HBITMAP MatToHBITMAP(cv::Mat& matImage); // OpenCV Mat �� HBITMAP ��ȯ �Լ�
	void CreateBitmapInfo(int nWidth, int nHeight, int nBpp); // Bitmap ������ �����ϴ� �Լ�.

	// Implementation
public:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

	// Event Handlers
public:
	afx_msg void OnBnClickedBtnImgLoad();
	afx_msg void OnBnClickedBtnImgSave();
	afx_msg void OnDestroy();
};
