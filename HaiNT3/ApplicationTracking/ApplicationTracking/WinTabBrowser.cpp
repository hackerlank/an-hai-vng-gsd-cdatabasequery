#pragma once
#include "StdAfx.h"
#include "WinTabBrowser.h"

CWinTabBrowser::CWinTabBrowser(BSTR strTitle, BSTR strURL)
{
	m_strTitle.Format(_T("%s"), strTitle);
	m_strURL.Format(_T("%s"), strURL);
}
	
CWinTabBrowser::CWinTabBrowser(CString pstrTitle, CString pstrURL)
{
	m_strTitle = pstrTitle;
	m_strURL = pstrURL;
}

CWinTabBrowser::~CWinTabBrowser(void)
{
	
}

CString CWinTabBrowser::GetTitle()
{
	return m_strTitle;
}
CString CWinTabBrowser::GetURL()
{
	return m_strURL;
}

BOOL CWinTabBrowser::CompareWinTab(const CWinTabBrowser* winTab)
{
	if(m_strTitle.Compare(winTab->GetTitle()) != 0)
	{
		return FALSE;
	}
	if(CompareServerHost(winTab->GetURL()))
	{
		return FALSE;
	}
	return FALSE;
}

BOOL CWinTabBrowser::CompareServerHost(const TCHAR* pstrURL)
{
	if(wcscmp( GetServerHost(m_strURL.GetBuffer()), GetServerHost(pstrURL)) == 0)
	{
		return TRUE;
	}
	return FALSE;
}


CString CWinTabBrowser::GetServerHost(const TCHAR* pstrURL)
{

	CString strHost;//(pstrURL);
	strHost.Format(_T("%s"), pstrURL);
	int iIndex = strHost.Find(_T("https://"), 0);
	if(iIndex >= 0)
	{
		strHost.Delete(iIndex,8);
	}
	iIndex = strHost.Find(_T("http://"), 0);
	if(iIndex >= 0)
	{
		strHost.Delete(iIndex,7);
	}

	iIndex = strHost.Find(L"/");

	strHost.Delete(iIndex, strHost.GetLength() - iIndex);
	return strHost;
}

CString CWinTabBrowser::GetServerHostAndPath(const TCHAR* pstrURL)
{

	CString strHost;//(pstrURL);
	strHost.Format(_T("%s"), pstrURL);
	int iIndex = strHost.Find(_T("https://"), 0);
	if(iIndex >= 0)
	{
		strHost.Delete(iIndex,8);
	}
	iIndex = strHost.Find(_T("http://"), 0);
	if(iIndex >= 0)
	{
		strHost.Delete(iIndex,7);
	}

	iIndex = strHost.Find(L"/");
	iIndex = strHost.Find(L"/", iIndex +1);
	strHost.Delete(iIndex, strHost.GetLength() - iIndex);
	return strHost;
}

