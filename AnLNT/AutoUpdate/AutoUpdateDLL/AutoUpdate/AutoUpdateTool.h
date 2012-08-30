#pragma once


#include "Launcher.h"

class  CAutoUpdateTool
{
protected:

	CString m_strSourcePath;
	CString m_strToken;
	CString m_strTempSourcePath;

	CLauncher *m_pAutoLauncher;
	CString m_strLogFilePath;

public:


	CAutoUpdateTool();
	BOOL Create(CLauncher *pAutoLauncher, LPCTSTR strToken);
	BOOL Update();
	CString GetName();

	virtual ~CAutoUpdateTool(void);
protected:
	BOOL CloneSource();
	BOOL RunAutoLauncher();
	BOOL Compare();
	BOOL RemoveTempSource();
	void WriteLog(const CString &strLog);
};