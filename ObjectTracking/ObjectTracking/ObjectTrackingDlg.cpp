// ObjectTrackingDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ObjectTracking.h"
#include "ObjectTrackingDlg.h"
#include "afxdialogex.h"

// 메모리 누수 점검 헤더
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CObjectTrackingDlg dialog

CObjectTrackingDlg::CObjectTrackingDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OBJECTTRACKING_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CObjectTrackingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

void CObjectTrackingDlg::DrawImage()
{
    CClientDC dc(GetDlgItem(IDC_PICTURE_VIEW));

    CRect rect;
    GetDlgItem(IDC_PICTURE_VIEW)->GetClientRect(&rect);

    const cv::Mat& matImage = viewModel.GetImage();
    if (matImage.empty()) return;

    // Bitmap 정보 업데이트
    CreateBitmapInfo(matImage.cols, matImage.rows, matImage.channels() * 8);

    SetStretchBltMode(dc.GetSafeHdc(), COLORONCOLOR);
    StretchDIBits(dc.GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
        matImage.cols, matImage.rows, matImage.data,
        m_pBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

BEGIN_MESSAGE_MAP(CObjectTrackingDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_GETMINMAXINFO()
    ON_BN_CLICKED(IDC_BTN_IMG_LOAD, &CObjectTrackingDlg::OnBnClickedBtnImgLoad)
    ON_BN_CLICKED(IDC_BTN_IMG_SAVE, &CObjectTrackingDlg::OnBnClickedBtnImgSave)
    ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CObjectTrackingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 시스템 메뉴에 "About" 추가
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        CString strAboutMenu;
        if (strAboutMenu.LoadString(IDS_ABOUTBOX))
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 아이콘 설정
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return TRUE;
}

void CObjectTrackingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void CObjectTrackingDlg::OnPaint()
{
    DrawImage();
    CDialogEx::OnPaint();
}

HCURSOR CObjectTrackingDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CObjectTrackingDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    lpMMI->ptMinTrackSize = CPoint(1920, 1080);
    CDialogEx::OnGetMinMaxInfo(lpMMI);
}

// 🔹 **ViewModel을 활용한 이미지 로드**
void CObjectTrackingDlg::OnBnClickedBtnImgLoad()
{
    CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY,
        _T("Image Files (*.jpg;*.bmp;*.png)|*.jpg;*.bmp;*.png|All Files (*.*)|*.*||"));

    if (fileDlg.DoModal() == IDOK)
    {
        CString path = fileDlg.GetPathName();
        std::string strPath(CT2CA(path));

        if (viewModel.LoadImage(strPath))
        {
            DrawImage();
        }
        else
        {
            AfxMessageBox(_T("이미지를 불러올 수 없습니다."));
        }
    }
}

// 🔹 **ViewModel을 활용한 이미지 저장**
void CObjectTrackingDlg::OnBnClickedBtnImgSave()
{
    if (viewModel.GetImage().empty())
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

        if (viewModel.SaveImage(strPath))
        {
            AfxMessageBox(_T("이미지를 저장했습니다."));
        }
        else
        {
            AfxMessageBox(_T("이미지를 저장할 수 없습니다."));
        }
    }
}

// 🔹 **메모리 해제 및 리소스 정리**
void CObjectTrackingDlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    // Bitmap 정보 해제
    if (m_pBitmapInfo != nullptr)
    {
        delete[] reinterpret_cast<BYTE*>(m_pBitmapInfo);
        m_pBitmapInfo = nullptr;
    }
}
