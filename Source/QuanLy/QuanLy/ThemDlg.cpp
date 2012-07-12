// ThemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QuanLy.h"
#include "ThemDlg.h"


// CThemDlg dialog

IMPLEMENT_DYNAMIC(CThemDlg, CDialog)

CThemDlg::CThemDlg(NHANVIEN* nhanVien /*=NULL*/, CWnd* pParent /*=NULL*/)
	: CDialog(CThemDlg::IDD, pParent)
{
	if(nhanVien != NULL)
	{
		m_strTenNhanVien =  nhanVien->strTenNhanVien;
		m_strPhongBan =  nhanVien->strTenPhongBan;
		m_strSoDienThoai = nhanVien->strSoDienThoai;
		m_strDiaChi = nhanVien->strDiaChi;
		/*_tcscpy(m_strTenNhanVien, nhanVien->strTenNhanVien);
		_tcscpy(m_strPhongBan, nhanVien->strTenPhongBan);
		_tcscpy(m_strSoDienThoai, nhanVien->strSoDienThoai);
		_tcscpy(m_strDiaChi, nhanVien->strDiaChi);*/
		if(nhanVien->cGioiTinh = 0)
		{
			m_strGioiTinh = _T("Nu");
		}else
			m_strGioiTinh = _T("Nam");
		m_bIsEdit = true;
		m_iMaNhanVien = nhanVien->iMaNhanVien;
	}
	else
	{
		m_bIsEdit = false;
	}
}

CThemDlg::~CThemDlg()
{
}

void CThemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Text(pDX, IDC_EDT_HOTEN, m_strTenNhanVien);
	DDV_MaxChars(pDX, m_strTenNhanVien, MAX_NAME);

	DDX_Text(pDX, IDC_CB_PHONGBAN, m_strPhongBan);
	DDV_MaxChars(pDX, m_strPhongBan, MAX_NAME);

	DDX_Text(pDX, IDC_CB_GIOITINH, m_strGioiTinh);
	DDV_MaxChars(pDX, m_strGioiTinh, 3);

	DDX_Text(pDX, IDC_EDT_SODIENTHOAI, m_strSoDienThoai);
	DDV_MaxChars(pDX, m_strSoDienThoai, MAX_PHONE);

	DDX_Text(pDX, IDC_EDT_DIACHI, m_strDiaChi);
	DDV_MaxChars(pDX, m_strDiaChi, MAX_ADDRESS);

}


BEGIN_MESSAGE_MAP(CThemDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CThemDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CThemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	if(m_bIsEdit)
	{
		SetWindowText(_T("Thay đổi thông tin nhân viên"));
		UpdateData(FALSE);
	}
	return TRUE;
}
// CThemDlg message handlers

void CThemDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CMySqlNhanVienDAO NhanVienDAO("","","","");
	if(NhanVienDAO.AddNhanVien(InitNhanVien()))
	{
		OnOK();
	}
}
NHANVIEN CThemDlg::InitNhanVien()
{
	UpdateData(TRUE);
	NHANVIEN nhanVien;
	_tcscpy(nhanVien.strTenNhanVien, m_strTenNhanVien);
	_tcscpy(nhanVien.strTenPhongBan, m_strPhongBan);
	_tcscpy(nhanVien.strSoDienThoai, m_strSoDienThoai);
	_tcscpy(nhanVien.strDiaChi, m_strDiaChi);
	if(m_strGioiTinh == _T("Name"))
	{
		nhanVien.cGioiTinh = 1;
	}
	else
		nhanVien.cGioiTinh = 0;
	return nhanVien;
}
