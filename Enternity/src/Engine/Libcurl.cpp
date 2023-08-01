#include "Libcurl.h"
#include <assert.h>

#include <filesystem>
#include <atlbase.h>
#include <atlconv.h>



#pragma comment(lib, "ws2_32")

class Libcurl;
union   //用于转换类成员方法指针到普通函数指针(地址相同)
{
	void(*ThreadProc)(LPVOID pvParam);
	void (Libcurl::*MemberProc)(LPVOID pvParam);
} Proc;

Libcurl::Libcurl(void)
	: m_curlMulti(NULL)
	, m_running(false)
	, m_thread(NULL)
{
	if (!m_curlMulti) {
		m_curlMulti = curl_multi_init();
	}
}


Libcurl::~Libcurl(void)
{
	if (m_curlMulti) {
		curl_multi_cleanup(m_curlMulti);
	}
}

Libcurl * Libcurl::GetInstance()
{
	static Libcurl * s_instance = nullptr;
	if (s_instance == nullptr)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		s_instance = new Libcurl;
	}
	return s_instance;
}

bool Libcurl::setPort(const char* lpUrl, LibcurlFlag libCurlFlg, long port)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		if (port == it->second->m_nPort)
			return true;
		it->second->m_nPort = port;
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_PORT, it->second->m_nPort);
	}
	return false;
}

bool Libcurl::setTimeout(const char* lpUrl, LibcurlFlag libCurlFlg, int nSecond)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		if (nSecond < 0)
			return false;
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_TIMEOUT, nSecond);
	}
	return false;
}

bool Libcurl::setConnectTimeout(const char* lpUrl, LibcurlFlag libCurlFlg, int nSecond)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		if (nSecond < 0)
			return false;
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_CONNECTTIMEOUT, nSecond);
	}
	return false;
}

bool Libcurl::setUserAgent(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpAgent)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		if (NULL == lpAgent)
			return false;
		size_t nLen = strlen(lpAgent);
		if (nLen == 0)
			return false;
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_USERAGENT, lpAgent);
	}
	return false;
}

bool Libcurl::setResumeFrom(const char* lpUrl, LibcurlFlag libCurlFlg, long lPos)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		if (lPos < 0)
			return false;
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_RESUME_FROM, lPos);
	}
	return false;
}

bool Libcurl::setResumeFromLarge(const char* lpUrl, LibcurlFlag libCurlFlg, uint64_t llPos)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		if (llPos < 0)
			return false;
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_RESUME_FROM_LARGE, llPos);
	}
	return false;
}

bool Libcurl::addHeader(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpKey, const char* lpValue)
{
	assert(lpKey != NULL && lpValue != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		size_t nLen1 = strlen(lpKey), nLen2 = strlen(lpValue);
		assert(nLen1 > 0 && nLen2 > 0);
		std::string strHeader(lpKey);
		strHeader.append(": ");
		strHeader.append(lpValue);
		it->second->m_curlList = curl_slist_append(it->second->m_curlList, strHeader.c_str());
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_HTTPHEADER, it->second->m_curlList);
	}
	return false;
}

bool Libcurl::addHeader(HttpRequest* httpRequest, const char* lpKey, const char* lpValue)
{
	size_t nLen1 = strlen(lpKey), nLen2 = strlen(lpValue);
	assert(nLen1 > 0 && nLen2 > 0);
	std::string strHeader(lpKey);
	strHeader.append(": ");
	strHeader.append(lpValue);
	httpRequest->m_curlList = curl_slist_append(httpRequest->m_curlList, strHeader.c_str());
	return CURLE_OK == curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_HTTPHEADER, httpRequest->m_curlList);
}

void Libcurl::clearHeaderList(const char* lpUrl, LibcurlFlag libCurlFlg)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end() && it->second->m_curlList)
	{
		curl_slist_free_all(it->second->m_curlList);
		it->second->m_curlList = NULL;
	}
}

bool Libcurl::setCookie(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpCookie)
{
	assert(lpCookie != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_COOKIE, lpCookie);
	}
	return false;
}

bool Libcurl::setCookieFile(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpFilePath)
{
	assert(lpFilePath != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{		
		return CURLE_OK == curl_easy_setopt(it->second->m_pCurl, CURLOPT_COOKIEFILE, lpFilePath);
	}
	return false;
}

const char* Libcurl::getError(const char* lpUrl, LibcurlFlag libCurlFlg) const
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
		return curl_easy_strerror(it->second->m_curlCode);
	return nullptr;
}

void Libcurl::setCallback(const char* lpUrl, LibcurlFlag libCurlFlg, LibcurlCallback* pCallback, void* lpParam)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	auto it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		it->second->m_pCallbackParam = lpParam;
		it->second->m_pCallback = pCallback;
	}
}

void Libcurl::downloadToFile(const char* lpUrl, const char* lpFile, bool bSyn/* = false*/)
{
//	std::string key;
//	key.append(SEnumName<LibcurlFlag>::List[Lf_Download]).append(lpUrl);
//	m_mutex.lock();
//	if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
//		m_httpRequestList.find(key) != m_httpRequestList.end())
//	{
//		m_mutex.unlock();
//		return;
//	}
//	m_mutex.unlock();
//	HttpRequest* httpRequest = new HttpRequest;
//	httpRequest->m_bSyn = bSyn;
//	CURLcode code = curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
//	std::string savePath, partPath;
//	savePath.append(lpFile);
//	httpRequest->m_downFileSavePath = savePath;
//	partPath.append(savePath).append(".part");
//
//	if (!getDownloadFileInfo(httpRequest, httpRequest->m_fiRemote))
//	{
//		delete httpRequest;
//		return;
//	}
//	if (httpRequest->m_fiRemote.fileSize <= 0)
//	{
//		delete httpRequest;
//		return ;
//	}
//
//	FileInfo localFi;
//	getLocalFileInfo(savePath, localFi);
//	if (!memcmp(&localFi, &httpRequest->m_fiRemote, sizeof(FileInfo)))
//	{
//		m_httpRequestFinishList.insert(make_pair(key,httpRequest));
//		return ;
//	}
//// 
//// 	Libcurl libcurlDown;
//// 	libcurlDown.m_lastFileTime = remoteFi.lastWriteTime;
//
//	FileInfo partFi;
//	getLocalFileInfo(partPath, partFi);
//	if (partFi.fileSize > 0 && partFi.lastWriteTime == httpRequest->m_fiRemote.lastWriteTime)
//	{
//		curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_RESUME_FROM_LARGE, partFi.fileSize);
//	}
//	
//	//DeleteFileA(partPath.c_str());
//	pafstd::CharacterConverter::Ucs2StringBuffer wPartPath;
//	pafstd::CharacterConverter::UCS2_From_UTF8(wPartPath, partPath.c_str(), (uint32_t)partPath.length());
//	httpRequest->m_hFile = CreateFileW(wPartPath.getBuffer(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (INVALID_HANDLE_VALUE == httpRequest->m_hFile)
//	{
//		delete httpRequest;
//		return ;
//	}
//
//	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
//	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
//	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_NOPROGRESS, 0);
//	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
//	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_PROGRESSDATA, httpRequest);
//	httpRequest->m_lfFlag = Lf_Download;
//	httpRequest->m_strRespons.clear();
//	addCurlHandler(key, httpRequest);
	//开始执行请求
// 	httpRequest->m_curlCode = curl_easy_perform(m_pCurl);
// 	
// 	if (m_lastFileTime > 0)
// 	{
// 		::SetFileTime(m_hFile, (FILETIME*)&m_lastFileTime, (FILETIME*)&m_lastFileTime, (FILETIME*)&m_lastFileTime);
// 	}
// 	CloseHandle(m_hFile);
// 	m_hFile = INVALID_HANDLE_VALUE;
// 	return CURLE_OK == m_curlCode;
}

void Libcurl::post(const char* lpUrl, const char* lpData, bool bSyn/* = false*/)
{
	assert(lpData != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Post]).append(lpUrl);
	m_mutex.lock();
	if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
		m_httpRequestList.find(key) != m_httpRequestList.end())
	{
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
	HttpRequest* httpRequest = new HttpRequest;
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POST, 1);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDS, lpData);
	//curl_easy_setopt(m_pCurl, CURLOPT_POSTFIELDSIZE, lpData);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	httpRequest->m_lfFlag = Lf_Post;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}

void Libcurl::post(const char* lpUrl, unsigned char* lpData, unsigned int nSize, bool bSyn/* = false*/)
{
	assert(lpData != NULL && nSize > 0);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Post]).append(lpUrl);
	m_mutex.lock();
	if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
		m_httpRequestList.find(key) != m_httpRequestList.end())
	{
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
	HttpRequest* httpRequest = new HttpRequest;
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POST, 1);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDS, lpData);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDSIZE, nSize);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	httpRequest->m_lfFlag = Lf_Post;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}

void Libcurl::post(HttpRequest* httpRequest, const char* lpData, bool bSyn /*= false*/)
{
	assert(httpRequest != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Post]).append(httpRequest->m_strURL);
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POST, 1);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDS, lpData);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, httpRequest->m_strURL.c_str());
	httpRequest->m_lfFlag = Lf_Post;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}

void Libcurl::get(const char* lpUrl, bool bSyn/* = false*/)
{
	assert(lpUrl != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Get]).append(lpUrl);
	m_mutex.lock();
	if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
		m_httpRequestList.find(key) != m_httpRequestList.end())
	{
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
	HttpRequest* httpRequest = new HttpRequest;
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_FOLLOWLOCATION, 1);//支持重定向
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	httpRequest->m_lfFlag = Lf_Get;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}


void Libcurl::get(HttpRequest* httpRequest, bool bSyn /*= false*/)
{
	assert(httpRequest != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Get]).append(httpRequest->m_strURL);
	
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, httpRequest->m_strURL.c_str());
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_FOLLOWLOCATION, 1);//支持重定向
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	httpRequest->m_lfFlag = Lf_Get;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}

void Libcurl::patch(const char* lpUrl, const char* lpData, bool bSyn/* = false*/)
{
	assert(lpData != NULL); 
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Patch]).append(lpUrl);
	m_mutex.lock();
	if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
		m_httpRequestList.find(key) != m_httpRequestList.end())
	{
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
	HttpRequest* httpRequest = new HttpRequest;
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_CUSTOMREQUEST, "PATCH");
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDS, lpData);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	httpRequest->m_lfFlag = Lf_Patch;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}


void Libcurl::patch(const char* lpUrl, unsigned char* lpData, unsigned int nSize, bool bSyn/* = false*/)
{
	assert(lpData != NULL && nSize > 0); 
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Patch]).append(lpUrl);
	m_mutex.lock();
	if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
		m_httpRequestList.find(key) != m_httpRequestList.end())
	{
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
	HttpRequest* httpRequest = new HttpRequest;
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_CUSTOMREQUEST, "PATCH");
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDS, lpData);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDSIZE, nSize);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	httpRequest->m_lfFlag = Lf_Patch;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}


void Libcurl::patch(HttpRequest* httpRequest, const char* lpData, bool bSyn /*= false*/)
{
	assert(httpRequest != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Patch]).append(httpRequest->m_strURL);
	
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_CUSTOMREQUEST, "PATCH");
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDS, lpData);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, httpRequest->m_strURL.c_str());
	httpRequest->m_lfFlag = Lf_Patch;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}

void Libcurl::deleteRequest(const char* lpUrl, bool bSyn/* = false*/)
{
	assert(lpUrl != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Delete]).append(lpUrl);
	m_mutex.lock();
	if (m_httpRequestFinishList.find(key)!=m_httpRequestFinishList.end() || 
		m_httpRequestList.find(key)!=m_httpRequestList.end())
	{
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
	HttpRequest* httpRequest = new HttpRequest;
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_CUSTOMREQUEST, "DELETE");
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_FOLLOWLOCATION, 1);//支持重定向
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	httpRequest->m_lfFlag = Lf_Delete;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}

void Libcurl::deleteRequest(HttpRequest* httpRequest, bool bSyn /*= false*/)
{
	assert(httpRequest != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Delete]).append(httpRequest->m_strURL);
	
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_CUSTOMREQUEST, "DELETE");
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, httpRequest->m_strURL.c_str());
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_FOLLOWLOCATION, 1);//支持重定向
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	httpRequest->m_lfFlag = Lf_Delete;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}

void Libcurl::uploadFile(const char* lpUrl, const char* lpFile, bool bSyn /*= false*/)
{
	//std::string key;
	//key.append(SEnumName<LibcurlFlag>::List[Lf_Upload]).append(lpUrl);
	//m_mutex.lock();
	//if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
	//	m_httpRequestList.find(key) != m_httpRequestList.end())
	//{
	//	m_mutex.unlock();
	//	return;
	//}
	//m_mutex.unlock();

	//HttpRequest* httpRequest = new HttpRequest;
	//httpRequest->m_bSyn = bSyn;
	//httpRequest->m_lfFlag = Lf_Upload;

	//std::string nativePath;
	//nativePath.append(lpFile);
	//FileInfo nativeFi;
	//getLocalFileInfo(nativePath, nativeFi);
	//httpRequest->m_blobData = pafstd::Blob::New(uint32_t(nativeFi.fileSize));

	//pafstd::CharacterConverter::Ucs2StringBuffer wNativePath;
	//pafstd::CharacterConverter::UCS2_From_UTF8(wNativePath, nativePath.c_str(), (uint32_t)nativePath.length());
	//httpRequest->m_hFile = CreateFileW(wNativePath.getBuffer(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//if (INVALID_HANDLE_VALUE == httpRequest->m_hFile)
	//{
	//	delete httpRequest;
	//	return;
	//}
	//uint32_t readCount;
	//ReadFile(httpRequest->m_hFile, httpRequest->m_blobData->getData(), 
	//	httpRequest->m_blobData->getLength(), (DWORD*)&readCount,NULL);
	//if (readCount != nativeFi.fileSize)
	//{
	//	delete httpRequest;
	//	return;
	//}
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);

	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_VERBOSE, 1L);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POST, 1L);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_READDATA, httpRequest->m_hFile);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDSIZE, nativeFi.fileSize);
	//curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_POSTFIELDS, httpRequest->m_blobData->getData());
	//httpRequest->m_strRespons.clear();
	//addCurlHandler(key, httpRequest);
}

void Libcurl::removeFile(const char* lpUrl, const char* lpFile, bool bSyn /*= false*/)
{
	assert(lpUrl != NULL);
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[Lf_Remove]).append(lpUrl);
	m_mutex.lock();
	if (m_httpRequestFinishList.find(key) != m_httpRequestFinishList.end() ||
		m_httpRequestList.find(key) != m_httpRequestList.end())
	{
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
	HttpRequest* httpRequest = new HttpRequest;
	httpRequest->m_bSyn = bSyn;
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_WRITEDATA, httpRequest);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_URL, lpUrl);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_FOLLOWLOCATION, 1);//支持重定向
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_SSL_VERIFYHOST, 0L);
	httpRequest->m_lfFlag = Lf_Remove;
	httpRequest->m_strRespons.clear();
	addCurlHandler(key, httpRequest);
}


int Libcurl::getHttpRequest(const char* lpUrl, LibcurlFlag libCurlFlg,HttpRequest **httpRequest)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	m_mutex.lock();
	auto it = m_httpRequestFinishList.find(key);
	if (it != m_httpRequestFinishList.end())
	{
		*httpRequest = it->second;
		m_mutex.unlock();
		return 1;
	}
	it = m_httpRequestList.find(key);
	if (it != m_httpRequestList.end())
	{
		*httpRequest = it->second;
		m_mutex.unlock();
		return 0;
	}
	m_mutex.unlock();
	return -1;
}

void Libcurl::removeFinishHttpRequest(const char* lpUrl, LibcurlFlag libCurlFlg)
{
	std::string key;
	key.append(SEnumName<LibcurlFlag>::List[libCurlFlg]).append(lpUrl);
	m_mutex.lock();
	auto it = m_httpRequestFinishList.find(key);
	if (it != m_httpRequestFinishList.end())
	{
		delete it->second;
		m_httpRequestFinishList.erase(it);
		m_mutex.unlock();
		return;
	}
	m_mutex.unlock();
}

bool Libcurl::getDownloadFileInfo(HttpRequest* httpRequest, FileInfo &fi)
{
 	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_HEADER, 1L);
 	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_NOBODY, 1L);
 	curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_FILETIME, 1L);
	CURLcode curlCode = curl_easy_perform(httpRequest->m_pCurl);
	if (curlCode == CURLE_OK)
	{
		curl_easy_getinfo(httpRequest->m_pCurl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &fi.fileSize);
		long lastWriteTime;
		curl_easy_getinfo(httpRequest->m_pCurl, CURLINFO_FILETIME, &lastWriteTime);
		FILETIME ft;
		LONGLONG ll = Int32x32To64(lastWriteTime, 10000000) + 116444736000000000;
		ft.dwLowDateTime = (DWORD)ll;
		ft.dwHighDateTime = (DWORD)(ll >> 32);

		fi.lastWriteTime = *(uint64_t*)&ft;
		//httpRequest->m_lastFileTime = fi.lastWriteTime;
		curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_HEADER, 0L);
		curl_easy_setopt(httpRequest->m_pCurl, CURLOPT_NOBODY, 0L);
		return true;
	}
	return false;
}

bool Libcurl::getLocalFileInfo(const std::string& filepath, FileInfo &fi) const
{
	//struct stat localfileStat;
	//fs::path fsPath = fs::u8path(filepath.c_str());
	//if (0 == stat(fsPath.string().c_str(), &localfileStat))
	//{
	//	fi.fileSize = localfileStat.st_size;
	//	FILETIME localFt;
	//	LONGLONG ll = Int32x32To64(localfileStat.st_mtime, 10000000) + 116444736000000000;
	//	localFt.dwLowDateTime = (DWORD)ll;
	//	localFt.dwHighDateTime = (DWORD)(ll >> 32);
	//	fi.lastWriteTime = *(uint64_t*)&localFt;
	//	return true;
	//}
	return false;
}

void Libcurl::addCurlHandler(const std::string& listKey, HttpRequest* httpRequest)
{
	if (httpRequest->m_bSyn)
	{
		httpRequest->m_curlCode = curl_easy_perform(httpRequest->m_pCurl);
		long response_code = 1000;

		curl_easy_getinfo(httpRequest->m_pCurl, CURLINFO_RESPONSE_CODE, &response_code);


		httpRequest->m_status = static_cast<int>(response_code);

		if (httpRequest->m_lfFlag == Lf_Download)
		{
			std::string partPath;
			FileInfo fi;
			partPath.append(httpRequest->m_downFileSavePath).append(".part");
			if (httpRequest->m_fiRemote.lastWriteTime > 0)
			{
				::SetFileTime(httpRequest->m_hFile, (FILETIME*)&(httpRequest->m_fiRemote.lastWriteTime),
					(FILETIME*)&(httpRequest->m_fiRemote.lastWriteTime), (FILETIME*)&(httpRequest->m_fiRemote.lastWriteTime));
			}
			CloseHandle(httpRequest->m_hFile);
			httpRequest->m_hFile = INVALID_HANDLE_VALUE;
			getLocalFileInfo(partPath, fi);
			if (fi.fileSize == httpRequest->m_fiRemote.fileSize)
			{
				remove(httpRequest->m_downFileSavePath.c_str());
				rename(partPath.c_str(), httpRequest->m_downFileSavePath.c_str());
			}
		}
		m_mutex.lock();
		m_httpRequestFinishList.insert(make_pair(listKey, httpRequest));
		m_mutex.unlock();
	}
	else
	{
		curl_multi_add_handle(m_curlMulti, httpRequest->m_pCurl);
		if (!m_thread)
		{
			Proc.MemberProc = &Libcurl::run;
			m_running = true;
			m_thread = CreateThread(0, 0, LPTHREAD_START_ROUTINE(Proc.ThreadProc), this, 0, 0);
		}
		m_mutex.lock();// 这里要加锁，因为是外面调用，有请求过来就唤醒线程
		m_httpRequestList.insert(make_pair(listKey, httpRequest));
		m_mutex.unlock();
	}
}

size_t Libcurl::WriteCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam)
{
	//把下载到的数据以追加的方式写入文件(一定要有a，否则前面写入的内容就会被覆盖了)
	HttpRequest* httpRequest = (HttpRequest*)pParam;
	size_t dwWritten = 0;
	switch (httpRequest->m_lfFlag)
	{
	case Lf_Download://下载
	{
		if (httpRequest->m_hFile == INVALID_HANDLE_VALUE)
			return 0;
		if (!WriteFile(httpRequest->m_hFile, pBuffer, (DWORD)(nSize*nMemByte), (DWORD*)&dwWritten, NULL))
			return 0;
	}
	break;
	case Lf_Post://Post数据
	case Lf_Patch://Patch数据
	case Lf_Get://Get数据
	case Lf_Delete://Delete数据
	case Lf_Upload://uploadFile
	case Lf_Remove:
	{
		httpRequest->m_strRespons.append((const char*)pBuffer, nSize*nMemByte);
		dwWritten = nSize * nMemByte;
	}
	break;
	case Lf_None://未定义
		break;
	}
	return dwWritten;
}

size_t Libcurl::HeaderCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam)
{
	HttpRequest* pThis = (HttpRequest*)pParam;
	return 0;
}

int Libcurl::ProgressCallback(void *pParam, double dltotal, double dlnow, double ultotal, double ulnow)
{
	HttpRequest* httpRequest = (HttpRequest*)pParam;
	if (httpRequest->m_pCallback)
	{
		httpRequest->m_pCallback->progress(httpRequest->m_pCallbackParam, dltotal, dlnow);
	}
	return 0;
}

int Libcurl::curlMultiSelect(CURLM * curlM)
{
	struct timeval timeoutTv;
	fd_set  fdRead;
	fd_set  fdWrite;
	fd_set  fdExcept;
	int    maxFd = -1;
	FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	FD_ZERO(&fdExcept);

	timeoutTv.tv_sec = 1;
	timeoutTv.tv_usec = 0;

	// 获取multi curl需要监听的文件描述符集合 fd_set //   
	curl_multi_fdset(curlM, &fdRead, &fdWrite, &fdExcept, &maxFd);

	int retCode = select(maxFd + 1, &fdRead, &fdWrite, NULL, &timeoutTv);
	switch (retCode)
	{
	case -1:
		return  retCode;
	case 0:
		return 0;
	default:
		return 1;
	}
	return 0;
}


void Libcurl::removeCurlHandler(CURL *pCurl)
{
	assert(m_httpRequestList.size() > 0);
	for (auto it = m_httpRequestList.begin(); m_httpRequestList.size()>0 &&it != m_httpRequestList.end(); ++it) 
	{
		HttpRequest *const psRequest = it->second;
		if (psRequest->m_pCurl != pCurl)
		{
			continue;
		}
		long response_code = 1000;
		curl_easy_getinfo(psRequest->m_pCurl, CURLINFO_RESPONSE_CODE, &response_code);
		psRequest->m_status = static_cast<int>(response_code);
		
		curl_multi_remove_handle(m_curlMulti, psRequest->m_pCurl);
		if (psRequest->m_lfFlag == Lf_Download )
		{
			std::string partPath;
			FileInfo fi;
			partPath.append(psRequest->m_downFileSavePath).append(".part");
			if (psRequest->m_fiRemote.lastWriteTime > 0)
			{
 				::SetFileTime(psRequest->m_hFile, (FILETIME*)&(psRequest->m_fiRemote.lastWriteTime), (FILETIME*)&(psRequest->m_fiRemote.lastWriteTime), (FILETIME*)&(psRequest->m_fiRemote.lastWriteTime));
			}
			CloseHandle(psRequest->m_hFile);
			psRequest->m_hFile = INVALID_HANDLE_VALUE;
			getLocalFileInfo(partPath, fi);
			if (fi.fileSize == psRequest->m_fiRemote.fileSize)
			{
				remove(psRequest->m_downFileSavePath.c_str());
				rename(partPath.c_str(), psRequest->m_downFileSavePath.c_str());
			}
			else
			{
				//if (psRequest->m_reConTimes <= 0)
				//{
				//	m_httpRequestFinishList.insert(make_pair(it->first, it->second));
				//	m_httpRequestList.erase(it);
				//	break;
				//}
				//psRequest->m_reConTimes--;
				//curl_easy_setopt(psRequest->m_pCurl, CURLOPT_RESUME_FROM_LARGE, fi.fileSize);

				//pafstd::CharacterConverter::Ucs2StringBuffer wPartPath;
				//pafstd::CharacterConverter::UCS2_From_UTF8(wPartPath, partPath.c_str(), (uint32_t)partPath.length());
				//psRequest->m_hFile = CreateFileW(wPartPath.getBuffer(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				//if (INVALID_HANDLE_VALUE == psRequest->m_hFile)
				//{
				//	m_httpRequestFinishList.insert(make_pair(it->first, it->second));
				//	m_httpRequestList.erase(it);
				//	break;
				//}
				//int64_t newPos = 0;
				//int64_t  indexOffset = 0;
				//if (!SetFilePointerEx(psRequest->m_hFile, *(PLARGE_INTEGER)&indexOffset, (PLARGE_INTEGER)&newPos, FILE_END) ||
				//	fi.fileSize != newPos)
				//{
				//	m_httpRequestFinishList.insert(make_pair(it->first, it->second));
				//	m_httpRequestList.erase(it);
				//	break;
				//}
				//curl_easy_pause(psRequest->m_pCurl, CURLPAUSE_RECV_CONT);
				//curl_multi_add_handle(m_curlMulti, psRequest->m_pCurl);
				break;
			}
		}
		m_httpRequestFinishList.insert(make_pair(it->first,it->second));
		m_httpRequestList.erase(it);
		break;
	}
}

void Libcurl::run(LPVOID pvParam)
{
	while (m_running)
	{
		m_mutex.lock();    // 在wait前，线程先加锁
		if (m_httpRequestList.size() <= 0)
		{   // 等待唤醒线程的新号才执行下面的
			m_mutex.unlock();
			continue;
		}

		int runningHandles;
		CURLMcode res = CURLM_CALL_MULTI_PERFORM;
		while (CURLM_CALL_MULTI_PERFORM == res)
		{
			res = curl_multi_perform(m_curlMulti, &runningHandles);
		}

		if (CURLM_OK != res)
		{
			break;
		}

		while (runningHandles > 0)
		{
			int rc = curlMultiSelect(m_curlMulti);
			if (-1 == rc)
			{
				break;
			}
			else
			{
				res = CURLM_CALL_MULTI_PERFORM;
				while (CURLM_CALL_MULTI_PERFORM == res)
				{
					res = curl_multi_perform(m_curlMulti, &runningHandles);
				}

				if (CURLM_OK != res)
				{
					break;
				}
			}
		}

		int msgsLeft;
		CURLMsg* msg;
		while ((msg = curl_multi_info_read(m_curlMulti, &msgsLeft)))
		{
			if (CURLMSG_DONE == msg->msg)   // 已经完成事件的handle
			{
				CURL* curl = msg->easy_handle;
				removeCurlHandler(curl);
			}
		}

		m_mutex.unlock();
	}
}







































































