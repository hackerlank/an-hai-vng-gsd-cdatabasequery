#include "StdAfx.h"
#include "AutoUpdateTool.h"
#include "FileServices.h"
#include "MyPath.h"
#include "FolderCloner.h"
#include "FolderCompare.h"
#include "FolderRemoving.h"



CAutoUpdateTool::CAutoUpdateTool()
{
	m_pAutoLauncher = NULL;
}

BOOL CAutoUpdateTool::Create( CLauncher *pAutoLauncher, LPCTSTR strToken )
{
	if (NULL == pAutoLauncher) {
		return FALSE;
	}

	m_strSourcePath = pAutoLauncher->GetSourcePath();
	
	m_strToken = strToken;
	m_pAutoLauncher = pAutoLauncher;

	CMyPath myPath;

	m_strLogFilePath = myPath.GetExeFilePath() + CString(L"\\log") + m_strToken + CString(L".txt");
	return TRUE;
}

CAutoUpdateTool::~CAutoUpdateTool(void)
{
	if (NULL != m_pAutoLauncher) {
		delete m_pAutoLauncher;
	}
}

BOOL CAutoUpdateTool::Update()
{
	CString strLog;

	if (NULL == m_pAutoLauncher) {

		strLog = L"Creating auto launcher is failed...";
		WriteLog(strLog);
		WriteLog(L"");

		return FALSE;
	}

	if (TRUE == CloneSource()) {

		if (FALSE ==  RunAutoLauncher()) {
			WriteLog(L"Running auto launcher is failed. There are some problems on the network connection or the auto launcher tool is out of date");
		}

		if (FALSE == Compare()) {
			WriteLog(L"Comparing folder is failed");
		}

	} else {

		WriteLog(L"Cloning folder is failed. Please check");
	}

	if (FALSE == RemoveTempSource()) {
		WriteLog(L"Removing temporary source is failed. Please remove temporary source manually");
	}

	strLog = m_pAutoLauncher->GetName() + L" update is complete...";
	WriteLog(strLog);
	WriteLog(L"");

	return TRUE;

}

BOOL CAutoUpdateTool::CloneSource()
{

	CMyPath myPath;

	CString strFolderName = myPath.GetShortFileName(m_strSourcePath);
	CString strSource = myPath.GetParentPath(m_strSourcePath);
	CString strDest = myPath.GetExeFilePath();

	CFolderCloner folderCloner(strSource, strDest, strFolderName);

	CString strLog = m_pAutoLauncher->GetName() + L" is cloning...";
	WriteLog(strLog);

	if (FALSE == folderCloner.Clone()) {
		return FALSE;
	}

	m_strTempSourcePath = strDest + CString(L"\\") + strFolderName;

	return TRUE;
}

BOOL CAutoUpdateTool::RunAutoLauncher()
{

	CString strLog = m_pAutoLauncher->GetName() + L" auto launcher is running ...";
	WriteLog(strLog);

	if (FALSE == m_pAutoLauncher->Run()) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAutoUpdateTool::Compare()
{

	CFolderCompare folderCompare(m_strSourcePath, m_strTempSourcePath);

	CMyPath myPath;

	CString strReportDirectory = myPath.GetExeFilePath() + L"\\Report";
	if (FALSE == myPath.IsDirectory(strReportDirectory)) {
		::CreateDirectory(strReportDirectory, NULL);
	}

	CString strResultFilePath = strReportDirectory  + L"\\"+ m_strToken + L"_" + m_pAutoLauncher->GetName() + L".txt";

	CString strLog = m_pAutoLauncher->GetName() + L" is comparing...";
	WriteLog(strLog);

	if (FALSE == folderCompare.Compare(strResultFilePath)) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL CAutoUpdateTool::RemoveTempSource()
{

	CFolderRemoving folderRemoving;
	
	CString strLog = m_pAutoLauncher->GetName() + L" is removing temporary source ...";
	WriteLog(strLog);


	CMyPath myPath;
	
	if (FALSE == myPath.IsDirectory(m_strTempSourcePath)) {
		return TRUE;
	}

	if (FALSE == folderRemoving.Remove(m_strTempSourcePath)) {
		return FALSE;
	}
	
	return TRUE;
}

CString CAutoUpdateTool::GetName()
{
	if (NULL == m_pAutoLauncher) {
		return L"";
	}
	return m_pAutoLauncher->GetName();
}

void CAutoUpdateTool::WriteLog( const CString &strLog )
{
	_tprintf(strLog + L"\n");

	CStdioFile fileWriter;
	CFileException fileException;

	if (fileWriter.Open(m_strLogFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary , &fileException)) {

		fileWriter.SeekToEnd();

		fileWriter.WriteString(strLog + L"\r\n");
	
		fileWriter.Close();
	} 
}