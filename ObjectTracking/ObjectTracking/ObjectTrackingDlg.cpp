#include "pch.h"
#include "framework.h"
#include "ObjectTracking.h"
#include "ObjectTrackingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CObjectTrackingDlg dialog

CObjectTrackingDlg::CObjectTrackingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OBJECTTRACKING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pBitmapInfo = nullptr;
	m_hBitmap = nullptr;
}

void CObjectTrackingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CObjectTrackingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_IMG_LOAD, &CObjectTrackingDlg::OnBnClickedBtnImgLoad)
	ON_BN_CLICKED(IDC_BTN_IMG_SAVE, &CObjectTrackingDlg::OnBnClickedBtnImgSave)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CObjectTrackingDlg message handlers

BOOL CObjectTrackingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return TRUE;
}

// Bitmap 정보 생성
void CObjectTrackingDlg::CreateBitmapInfo(int nWidth, int nHeight, int nBpp)
{
	try {
		ReleaseBitmap(); // 기존 Bitmap 해제

		if (nBpp == 8)
			m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
		else
			m_pBitmapInfo = (BITMAPINFO*) new BYTE[sizeof(BITMAPINFO)];

		m_pBitmapInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_pBitmapInfo->bmiHeader.biPlanes = 1;
		m_pBitmapInfo->bmiHeader.biBitCount = nBpp;
		m_pBitmapInfo->bmiHeader.biCompression = BI_RGB;
		m_pBitmapInfo->bmiHeader.biWidth = nWidth;
		m_pBitmapInfo->bmiHeader.biHeight = -nHeight; // 상하 반전 방지
	}
	catch (const std::exception& e) {
		AfxMessageBox(CString("Exception in CreateBitmapInfo: ") + CString(e.what()), MB_ICONERROR);
	}
}

// Picture Control에 이미지 그리기
void CObjectTrackingDlg::DrawImage()
{
	if (!m_pBitmapInfo || m_viewModel.GetImage()->empty()) return;

	try {
		CClientDC dc(GetDlgItem(IDC_PICTURE_VIEW));

		CRect rect;
		GetDlgItem(IDC_PICTURE_VIEW)->GetClientRect(&rect);

		SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
		StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(),
			0, 0, m_viewModel.GetImage()->cols, m_viewModel.GetImage()->rows,
			m_viewModel.GetImage()->data, m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	}
	catch (const std::exception& e) {
		AfxMessageBox(CString("Exception in DrawImage: ") + CString(e.what()), MB_ICONERROR);
	}
}

// Bitmap 해제
void CObjectTrackingDlg::ReleaseBitmap()
{
	if (m_pBitmapInfo) {
		delete[] reinterpret_cast<BYTE*>(m_pBitmapInfo);
		m_pBitmapInfo = nullptr;
	}

	if (m_hBitmap) {
		DeleteObject(m_hBitmap);
		m_hBitmap = nullptr;
	}
}

// OpenCV Mat → HBITMAP 변환
HBITMAP CObjectTrackingDlg::MatToHBITMAP(cv::Mat& matImage)
{
	if (matImage.empty()) return nullptr;

	cv::Mat tempImage;
	if (matImage.channels() == 1) {
		cv::cvtColor(matImage, tempImage, cv::COLOR_GRAY2BGR);
	}
	else {
		tempImage = matImage.clone();
	}

	BITMAPINFO bmpInfo = {};
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = tempImage.cols;
	bmpInfo.bmiHeader.biHeight = -tempImage.rows;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	HDC hDC = ::GetDC(NULL);
	void* pBits = nullptr;
	HBITMAP hBitmap = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, &pBits, NULL, 0);
	if (hBitmap) {
		memcpy(pBits, tempImage.data, tempImage.total() * tempImage.elemSize());
	}
	::ReleaseDC(NULL, hDC);
	return hBitmap;
}

void CObjectTrackingDlg::OnBnClickedBtnImgLoad()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY,
		_T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		std::string strPath(CT2A(path, CP_ACP));

		std::string errorMsg;
		if (m_viewModel.LoadImage(strPath, errorMsg))
		{
			std::shared_ptr<const cv::Mat> image = m_viewModel.GetImage(); // 🔹 Model 데이터 가져오기

			if (image && !image->empty()) 
			{
				CreateBitmapInfo(image->cols, image->rows, image->channels() * 8);
				DrawImage();
				AfxMessageBox(_T("Image loaded successfully!"));
			}
		}
		else
		{
			AfxMessageBox(CString("Failed to load image!\n") + CString(errorMsg.c_str()), MB_ICONERROR);
		}
	}
}

void CObjectTrackingDlg::OnBnClickedBtnImgSave()
{
	if (m_viewModel.GetImage()->empty())
	{
		AfxMessageBox(_T("이미지를 불러오지 못했습니다."), MB_ICONERROR);
		return;
	}

	CFileDialog fileDlg(FALSE, _T("jpg"), NULL, OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
		_T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||"));

	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		std::string strPath(CT2A(path, CP_UTF8));

		std::string errorMsg;
		if (m_viewModel.SaveImage(strPath, errorMsg))
		{
			AfxMessageBox(_T("Image saved successfully!"));
		}
		else
		{
			AfxMessageBox(CString("Failed to save image!\n") + CString(errorMsg.c_str()), MB_ICONERROR);
		}
	}
}


// 종료 시 메모리 해제
void CObjectTrackingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	ReleaseBitmap();
}
