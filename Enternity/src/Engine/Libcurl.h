#pragma once
/*****************************************
*封装Libcurl下载库
*/
#include "curl/curl.h"
#include <string>
#include <map>
#include <mutex>
#include "Blob.h"
#include "Common/Macro.h"

struct FileInfo
{
	uint64_t fileSize;
	uint64_t lastWriteTime;
	FileInfo()
	{
		fileSize = 0;
		lastWriteTime = 0;
	}
};

struct FileInfoEx
{
	bool		m_exist;
	FileInfo	m_info;
};


class LibcurlCallback
{
public:
	virtual void progress(void* lpParam, double dTotal, double bLoaded) = 0;
};

enum LibcurlFlag
{
	Lf_None = 0,
	Lf_Download,
	Lf_Post,
	Lf_Get,
	Lf_Patch,
	Lf_Delete,
	Lf_Upload,
	Lf_Remove,
};

template<typename EnumType>
struct SEnumName
{
	static const char* List[];
};

const char* SEnumName<LibcurlFlag>::List[] =
{
	"None",
	"Download",
	"Post",
	"Get",
	"Patch",
	"Delete",
	"Upload",
	"Remove"
};



struct HttpRequest
{
public:
	HttpRequest()
		: m_strURL("")
		, m_pCurl(NULL)
		, m_nPort(80)
		, m_hFile(INVALID_HANDLE_VALUE)
		, m_downFileSavePath("")
		, m_pCallback(NULL)
		, m_pCallbackParam(NULL)
		, m_curlCode(CURLE_OK)
		, m_lfFlag(Lf_None)
		, m_curlList(NULL)
		, m_strRespons("")
		, m_bSyn(false)
		, m_blobData(NULL)
		, m_status(0)
		, m_reConTimes(10)
	{
		m_pCurl = curl_easy_init();
	}
	~HttpRequest()
	{
		curl_easy_cleanup(m_pCurl);
		if (m_hFile != INVALID_HANDLE_VALUE)
		{
			if (m_fiRemote.lastWriteTime > 0)
			{
				SetFileTime(m_hFile, (FILETIME*)&m_fiRemote.lastWriteTime, (FILETIME*)&m_fiRemote.lastWriteTime, (FILETIME*)&m_fiRemote.lastWriteTime);
			}
			CloseHandle(m_hFile);
			m_hFile = INVALID_HANDLE_VALUE;
		}
		if (m_curlList)
		{
			curl_slist_free_all(m_curlList);
			m_curlList = NULL;
		}

		SAFE_DELETE_SET_NULL(m_blobData);
	}
public:
	std::string m_strURL;
	CURL	*m_pCurl;
	long	m_nPort;
	HANDLE	m_hFile;
	std::string m_downFileSavePath;
	CURLcode m_curlCode;
	std::string	m_strRespons;
	LibcurlFlag m_lfFlag;
	curl_slist *m_curlList;
	void	*m_pCallbackParam;
	LibcurlCallback	*m_pCallback;
	FileInfo m_fiRemote;
	uint32_t m_status;
	Enternity::Blob *m_blobData;	
	int m_reConTimes;
	bool m_bSyn;
};


class Libcurl
{
public:
	Libcurl(void);
	~Libcurl(void);
	/******************************************************************************
	*封装类的外部调用接口
	*/
	static Libcurl *GetInstance();
	bool setPort(const char* lpUrl, LibcurlFlag libCurlFlg,long port);											//设置连接端口号
	bool setTimeout(const char* lpUrl, LibcurlFlag libCurlFlg, int nSecond);										//设置执行超时（秒）
	bool setConnectTimeout(const char* lpUrl, LibcurlFlag libCurlFlg, int nSecond);								//设置连接超时（秒）
	bool setUserAgent(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpAgent);									//设置用户代理
	bool setResumeFrom(const char* lpUrl, LibcurlFlag libCurlFlg, long lPos);										//设置断点续传起始位置
	bool setResumeFromLarge(const char* lpUrl, LibcurlFlag libCurlFlg, uint64_t llPos);							//设置断点续传起始位置，针对大文件
	bool addHeader(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpKey, const char* lpValue);						//添加自定义头
	bool addHeader(HttpRequest* httpRequest, const char* lpKey, const char* lpValue);
	void clearHeaderList(const char* lpUrl, LibcurlFlag libCurlFlg);												//清理HTTP列表头
	bool setCookie(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpCookie);									//设置HTTP请求cookie
	bool setCookieFile(const char* lpUrl, LibcurlFlag libCurlFlg, const char* lpFilePath);								//设置HTTP请求cookie文件
	const char* getError(const char* lpUrl, LibcurlFlag libCurlFlg)const;										//获取错误详细信息
	void setCallback(const char* lpUrl, LibcurlFlag libCurlFlg, LibcurlCallback* pCallback, void* lpParam);		//设置下载进度回调
	void downloadToFile(const char* lpUrl, const char* lpFile, bool bSyn = false);					//下载文件到磁盘
	void post(HttpRequest* httpRequest, const char* lpData, bool bSyn = false);
	void post(const char* lpUrl, const char* lpData, bool bSyn = false);								//Post 字符串数据
	void post(const char* lpUrl, unsigned char* lpData, unsigned int nSize, bool bSyn = false); //Post 字符串或者二进制数据
	void get(HttpRequest* httpRequest, bool bSyn = false);
	void get(const char* lpUrl, bool bSyn = false);												//Get 请求
	void patch(HttpRequest* httpRequest, const char* lpData, bool bSyn = false);
	void patch(const char* lpUrl, const char* lpData, bool bSyn = false);							//Patch 字符串数据
	void patch(const char* lpUrl, unsigned char* lpData, unsigned int nSize, bool bSyn = false);//Patch 字符串或者二进制数据
	void deleteRequest(const char* lpUrl, bool bSyn = false);
	void deleteRequest(HttpRequest* httpRequest, bool bSyn = false);											//Delete 请求
	void uploadFile(const char* lpUrl, const char* lpFile, bool bSyn = false);
	void removeFile(const char* lpUrl, const char* lpFile, bool bSyn = false);							//获取Post/Get/Patch请求返回数据
	int getHttpRequest(const char* lpUrl, LibcurlFlag libCurlFlg, HttpRequest **httpRequest);
	
	void removeFinishHttpRequest(const char* lpUrl, LibcurlFlag libCurlFlg);
	bool getDownloadFileInfo(HttpRequest* httpRequest, FileInfo &fi);							// Get the file info on the server
	bool getLocalFileInfo(const std::string& filepath, FileInfo &fi) const;
	void addCurlHandler(const std::string& listKey,HttpRequest* httpRequest);


protected:
	static size_t	WriteCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static size_t	HeaderCallback(void* pBuffer, size_t nSize, size_t nMemByte, void* pParam);
	static int		ProgressCallback(void *pParam, double dltotal, double dlnow, double ultotal, double ulnow);

	void run(LPVOID pvParam);
	int curlMultiSelect(CURLM * curlM);
	void removeCurlHandler(CURL	*pCurl);
private:
	CURLM *m_curlMulti { nullptr };
	typedef std::map<std::string, HttpRequest*> HttpRequestContainer;
	HttpRequestContainer m_httpRequestList;
	HttpRequestContainer m_httpRequestFinishList;
	std::mutex m_mutex;

	HANDLE m_beginRequestEvent;
	HANDLE m_thread { nullptr };
	bool m_running{ false };
};

