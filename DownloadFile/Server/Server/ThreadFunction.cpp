#include "stdafx.h"
#include "ThreadFunction.h"
#include "Messages.h"
#include "MessageHandler.h"

DWORD WINAPI SocketAcceptThreadFunction( LPVOID lpParam ) {

	SOCKET *pSocket = (SOCKET*)lpParam ;
	SOCKET sListenSocket = *pSocket;
	SOCKET *psConnectSocket = NULL;

	while (true) {

		SOCKET sConnectSocket = INVALID_SOCKET;
		sConnectSocket = accept(sListenSocket, NULL, NULL);

		if (INVALID_SOCKET != sConnectSocket) {

			SOCKET *psConnectSocket = new SOCKET;
			*psConnectSocket = sConnectSocket;

			HANDLE hThread = CreateThread(NULL, 0,  SocketCommunicationThreadFunction, psConnectSocket, NULL, NULL);
		}
	}
	return 0;
}

DWORD WINAPI SocketCommunicationThreadFunction(LPVOID lpParam ) {

	SOCKET *pSocket = (SOCKET*)lpParam ;
	SOCKET sConnectSocket = *pSocket;
	delete pSocket;

	const int BUFFER_LENGTH = 512;
	char strBuffer[BUFFER_LENGTH] = {0};
	

	while (true) {

		MESSAGE_HEADER messageHeader;
		ZeroMemory(&messageHeader, sizeof(messageHeader));

		int iLastError = 0;
		
		::OutputDebugString(_T("Cho nhan message header\n"));
		int iBytesReceived = recv(sConnectSocket, (char*)&messageHeader, sizeof(MESSAGE_HEADER), 0);
		if (iBytesReceived != sizeof(MESSAGE_HEADER)) {
			return HandleError(sConnectSocket);
		}
		::OutputDebugString(_T("da nhan duoc message header\n"));
		switch(messageHeader.iType) {
			case DOWNLOAD_FILE:
				if (HandleDownloadFileMessage(sConnectSocket, messageHeader.iLength, &iLastError) == false) {
					return iLastError;
				}
				break;
		}
	}
	return 0;
}