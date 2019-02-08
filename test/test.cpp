// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <HPSocket.h>
#include <HPSocket-SSL.h>
#include <iostream>
#include <windows.h>
#include <filesystem>
namespace fs = std::filesystem;
//Listener
class CListenerImpl : public CHttpSyncClientListener
{
public:
	std::unique_ptr<IHttpSyncClient> m_pClient;
public:
	EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID) override;
	EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) override;

	EnHttpParseResult OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue) override;
	EnHttpParseResult OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID) override;
	EnHttpParseResult OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override;
	EnHttpParseResult OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength) override;
	EnHttpParseResult OnChunkComplete(IHttpClient* pSender, CONNID dwConnID) override;
	EnHttpParseResult OnMessageComplete(IHttpClient* pSender, CONNID dwConnID) override;
	EnHttpParseResult OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType) override;

	EnHandleResult OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved, BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen) override;
	EnHandleResult OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) override;
	EnHandleResult OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID) override;
};


EnHandleResult CListenerImpl::OnConnect(ITcpClient* pSender, CONNID dwConnID)
{
	return HR_OK;
}

EnHandleResult CListenerImpl::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation,
	int iErrorCode)
{
	return HR_OK;
}

EnHttpParseResult CListenerImpl::OnHeader(IHttpClient* pSender, CONNID dwConnID, LPCSTR lpszName, LPCSTR lpszValue)
{
	return HPR_OK;
}

EnHttpParseResult CListenerImpl::OnHeadersComplete(IHttpClient* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CListenerImpl::OnBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	auto hFile = pSender->GetExtra();
	if (nullptr != hFile)
	{
		::WriteFile(hFile, pData, iLength, nullptr, nullptr);
	}
	return HPR_OK;
}

EnHttpParseResult CListenerImpl::OnChunkHeader(IHttpClient* pSender, CONNID dwConnID, int iLength)
{
	return HPR_OK;
}

EnHttpParseResult CListenerImpl::OnChunkComplete(IHttpClient* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CListenerImpl::OnMessageComplete(IHttpClient* pSender, CONNID dwConnID)
{
	return HPR_OK;
}

EnHttpParseResult CListenerImpl::OnUpgrade(IHttpClient* pSender, CONNID dwConnID, EnHttpUpgradeType enUpgradeType)
{
	return HPR_OK;
}

EnHandleResult CListenerImpl::OnWSMessageHeader(IHttpClient* pSender, CONNID dwConnID, BOOL bFinal, BYTE iReserved,
	BYTE iOperationCode, const BYTE lpszMask[4], ULONGLONG ullBodyLen)
{
	return HR_OK;
}

EnHandleResult CListenerImpl::OnWSMessageBody(IHttpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
	return HR_OK;
}

EnHandleResult CListenerImpl::OnWSMessageComplete(IHttpClient* pSender, CONNID dwConnID)
{


	return HR_OK;
}

auto main() -> int
{
	HANDLE hFile{ nullptr };
	CListenerImpl c_listener;
	CHttpsSyncClientPtr tmp_client(&c_listener);
	auto local_path = fs::path("D:\\test.md");
	hFile = CreateFileW(local_path.c_str(), GENERIC_WRITE, NULL, nullptr, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
	tmp_client->SetupSSLContext(SSL_VM_NONE, nullptr, nullptr, nullptr);
	tmp_client->SetExtra(hFile);

	tmp_client->OpenUrl("GET", "https://raw.githubusercontent.com/ldcsaa/HP-Socket/master/README.md", nullptr, NULL, nullptr, NULL, TRUE);
	if (hFile != nullptr)
	{
		CloseHandle(hFile);
	}
	system("pause");
	
}
