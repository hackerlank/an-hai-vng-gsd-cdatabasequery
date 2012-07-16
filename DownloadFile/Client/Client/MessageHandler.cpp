#include "StdAfx.h"
#include "MessageHandler.h"

bool HandleDownloadFileMessage(int iLength, int *piLastError) {
	::OutputDebugString(_T("Nhảy vào hàm HandleDownloadFileMessage\n"));
	return true;
}

int HandleError(SOCKET socket) {

	int iError = WSAGetLastError();

	shutdown(socket, SD_BOTH);
	closesocket(socket);

	return iError;
}