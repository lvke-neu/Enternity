//#include "Engine/Engine.h"
//#include "Engine/AssetLoader.h"
//#include "Graphics/RHI/Renderer/Renderer.h"
//#include "Graphics/RHI/Texture/Texture.h"
//#include "Engine/BlobLoaderManager.h"
//#include "Engine/BlobLoader.h"
//#include "Engine/BlobHolder.h"
//#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
//#include "Graphics/RHI/Mesh/VertexDefine.h"
//#include "Graphics/RHI/Mesh/MeshBlobLoader.h"
//#include "Scene/Model/Model.h"
//#include "Engine/Blob.h"
//#include <glm/glm.hpp>
//
//using namespace Enternity;
//
//int main(int argc, const char** argv) {
//
//	Enternity::Engine::GetInstance().initialize();
//
//	std::string path = "model://assets/models/basic/Cube.fbx";
//
//	auto model = dynamic_cast<Model*>(Engine::GetInstance().getAssetLoader()->getAsset(path.c_str()));
//	int i = 0;
//	//std::string path = "mesh://primitive=plane";
//	//auto blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path.c_str());
//
//	//if (blobLoader)
//	//{
//	//	MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobLoader->createBlobHolder(path.c_str()));
//
//	//	if (meshBlobHolder)
//	//	{
//	//		meshBlobHolder->load(0);
//	//		while (!meshBlobHolder->isLoadSucceeded())
//	//		{
//
//	//		}
//	//		std::vector<Vertex_Positon_Normal_Texcoord> vertices;
//	//		vertices.resize(4);
//	//		std::vector<unsigned int> indices;
//	//		indices.resize(36);
//	//		memcpy_s(vertices.data(), meshBlobHolder->getMeshDesc().vertexDataSize,
//	//			(char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getMeshDesc().vertexDataOffset,
//	//			meshBlobHolder->getMeshDesc().vertexDataSize);
//	//		memcpy_s(indices.data(), meshBlobHolder->getMeshDesc().indexDataSize,
//	//			(char*)meshBlobHolder->getBlob()->getData() + meshBlobHolder->getMeshDesc().indexDataOffset,
//	//			meshBlobHolder->getMeshDesc().indexDataSize);
//	//		int i = 0;
//	//		i++;
//	//	}
//	//}
//
//	//std::string path = "renderer://assets/shaders/test/test2.rdr";
//	//Engine::GetInstance().getAssetLoader()->getAsset(path.c_str(),
//	//	[=](Asset* asset)
//	//	{
//	//		Renderer* rdr = dynamic_cast<Renderer*>(asset);
//	//		if (rdr && rdr->isLoadSucceeded())
//	//		{
//	//			rdr->bind();
//	//		}
//
//	//		int i = 0;
//	//		i++;
//	//	});
//
//	//path = "texture://assets/textures/atmosphere.png";
//	//auto asset = Engine::GetInstance().getAssetLoader()->getAsset(path.c_str());
//	//int i = 0;
//	//i++;
//
//
//
//	//std::string path = "renderer://assets/shaders/test/test2.rdr";
//
//	//Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRHIAsset(path.c_str(),
//	//	[=](RHIAsset* rhiAsset)
//	//	{
//	//		Renderer* rdr = dynamic_cast<Renderer*>(rhiAsset);
//	//		if (rdr && rdr->isLoadSucceeded())
//	//		{
//	//			rdr->bind();
//	//		}
//	//		
//	//		int i = 0;
//	//		i++;
//	//	});
//
//	//path = "renderer://assets/textures/atmosphere.png";
//	//Engine::GetInstance()
//
//
//	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
//
//	//if (blobLoader)
//	//{
//	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
//	//	blobHolder->load();
//	//	while (!blobHolder->isLoadSucceeded())
//	//	{
//	//		
//	//	}
//
//	//	RendererBlobHolder* rendererBlobHolder = (RendererBlobHolder*)blobHolder;
//
//	//	std::string vs((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().vertDataOffset,
//	//		rendererBlobHolder->getShaderDesc().vertDataSize);
//
//	//	std::string gs((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().geomDataOffset,
//	//		rendererBlobHolder->getShaderDesc().geomDataSize);
//
//	//	std::string ps((char*)rendererBlobHolder->getBlob()->getData() + rendererBlobHolder->getShaderDesc().fragDataOffset,
//	//		rendererBlobHolder->getShaderDesc().fragDataSize);
//
//	//	int i = 0;
//	//	i++;
//	//}
//
//	//std::string path = "texture://assets/textures/atmosphere.png";
//	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
//
//	//
//
//	//if (blobLoader)
//	//{
//	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
//	//	blobHolder->load();
//	//	while (!blobHolder->isLoadSucceeded())
//	//	{
//	//		
//	//	}
//	//}
//
//	//std::string path = "mesh://assets/models/nanosuit/nanosuit.obj";
//	//BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
//
//	//if (blobLoader)
//	//{
//	//	BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
//	//	blobHolder->load();
//	//	while (!blobHolder->isLoadSucceeded())
//	//	{
//	//		
//	//	}
//
//	//	MeshBlobHolder* meshBlobHolder = dynamic_cast<MeshBlobHolder*>(blobHolder);
//
//	//	int i = 0;
//	//	i++;
//	//}
//
//
//
//	Enternity::Engine::GetInstance().run();
//	Enternity::Engine::GetInstance().uninitialize();
//
//	return 0;
//}
//
//



#include <iostream>
#include <sstream>
#include <iomanip>
#include "Engine/Libcurl.h"

class  Utility
{
public:
	//获取GUID
	static std::string GenerateGuid();
	//获取当前系统时间(精确到毫秒)
	static uint64_t GetCurTime();

	//sha256加密
	static void GetSHA256(std::string& sha256str, const std::string& str);

};

std::string Utility::GenerateGuid()
{
    char buffer[64] = { 0 };
    GUID guid;
    if (CoCreateGuid(&guid))
    {
        return "";
    }
    sprintf_s(buffer, sizeof(buffer),
        "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2],
        guid.Data4[3], guid.Data4[4], guid.Data4[5],
        guid.Data4[6], guid.Data4[7]);
    return buffer;
}

uint64_t Utility::GetCurTime()
{
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return ms.count();
}

BOOL CalculateHash(BYTE* pData, DWORD dwDataLength, ALG_ID algHashType, BYTE** ppHashData, DWORD* pdwHashDataLength)
{
    HCRYPTPROV hCryptProv = NULL;
    HCRYPTHASH hCryptHash = NULL;
    BYTE* pHashData = NULL;
    DWORD dwHashDataLength = 0;
    DWORD dwTemp = 0;
    BOOL bRet = FALSE;


    do
    {
        // 获得指定CSP的密钥容器的句柄
        bRet = ::CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
        if (FALSE == bRet)
        {
            //ShowError("CryptAcquireContext");
            break;
        }

        // 创建一个HASH对象, 指定HASH算法
        bRet = ::CryptCreateHash(hCryptProv, algHashType, NULL, NULL, &hCryptHash);
        if (FALSE == bRet)
        {
            //ShowError("CryptCreateHash");
            break;
        }

        // 计算HASH数据
        bRet = ::CryptHashData(hCryptHash, pData, dwDataLength, 0);
        if (FALSE == bRet)
        {
            //ShowError("CryptHashData");
            break;
        }

        // 获取HASH结果的大小
        dwTemp = sizeof(dwHashDataLength);
        bRet = ::CryptGetHashParam(hCryptHash, HP_HASHSIZE, (BYTE*)(&dwHashDataLength), &dwTemp, 0);
        if (FALSE == bRet)
        {
            //ShowError("CryptGetHashParam");
            break;
        }

        // 申请内存
        pHashData = new BYTE[dwHashDataLength];
        if (NULL == pHashData)
        {
            bRet = FALSE;
            //ShowError("new");
            break;
        }
        ::RtlZeroMemory(pHashData, dwHashDataLength);

        // 获取HASH结果数据
        bRet = ::CryptGetHashParam(hCryptHash, HP_HASHVAL, pHashData, &dwHashDataLength, 0);
        if (FALSE == bRet)
        {
            //ShowError("CryptGetHashParam");
            break;
        }

        // 返回数据
        *ppHashData = pHashData;
        *pdwHashDataLength = dwHashDataLength;

    } while (FALSE);

    // 释放关闭
    if (FALSE == bRet)
    {
        if (pHashData)
        {
            delete[]pHashData;
            pHashData = NULL;
        }
    }
    if (hCryptHash)
    {
        ::CryptDestroyHash(hCryptHash);
    }
    if (hCryptProv)
    {
        ::CryptReleaseContext(hCryptProv, 0);
    }

    return bRet;
}

void Utility::GetSHA256(std::string& sha256strTemp, const std::string& str)
{
    //Sha256 sha256;
    //sha256str = sha256.getHexMessageDigest(str);

    BYTE* pHashData = NULL;
    DWORD dwHashDataLength = 0;

    CalculateHash((BYTE*)str.c_str(), str.size(), CALG_SHA_256, &pHashData, &dwHashDataLength);

    std::ostringstream o_s;
    o_s << std::hex;
    for (int it = 0; it != dwHashDataLength; ++it)
    {
        o_s << std::setw(2) << std::setfill('0') << static_cast<unsigned short>(pHashData[it]);
    }

    sha256strTemp = o_s.str();

    return;
}

Enternity::Blob* getBlob(const HttpRequest* httpRequest, bool autoRemoveRequest)
{
	if ((httpRequest->m_status == 200) && (httpRequest->m_strRespons.length() > 0))
	{
		Enternity::Blob* blob = new Enternity::Blob(httpRequest->m_strRespons.length());
		BYTE* blob_buffer = (BYTE*)blob->getData();
		memcpy(blob_buffer, httpRequest->m_strRespons.c_str(), httpRequest->m_strRespons.length());
		if (autoRemoveRequest)
		{
			Libcurl::GetInstance()->removeFinishHttpRequest(httpRequest->m_strURL.c_str(), LibcurlFlag::Lf_Get);
		}
		return blob;
	}
	if (autoRemoveRequest)
	{
		Libcurl::GetInstance()->removeFinishHttpRequest(httpRequest->m_strURL.c_str(), LibcurlFlag::Lf_Get);
	}
	return NULL;
}

Enternity::Blob* getHttpRequest(const char* url, bool bSyn = true, bool autoRemoveRequest = true)
{
	HttpRequest* httpRequest = NULL;
	if (!bSyn)
	{
		int httpRequestRes = Libcurl::GetInstance()->getHttpRequest(url, LibcurlFlag::Lf_Get, &httpRequest);
		if (1 == httpRequestRes)
		{
			return getBlob(httpRequest, autoRemoveRequest);
		}
		else if (0 == httpRequestRes)
		{
			return NULL;
		}
	}
	httpRequest = new HttpRequest;
	httpRequest->m_strURL = url;
	//for (auto header : m_headerList)
	//{
	//	if (header.first.empty() || header.second.empty())
	//		continue;
	//	Libcurl::GetInstance()->addHeader(httpRequest, header.first.c_str(), header.second.c_str());
	//}
	Libcurl::GetInstance()->get(httpRequest, bSyn);
	if (bSyn)
	{
		int httpRequestRes = Libcurl::GetInstance()->getHttpRequest(url, LibcurlFlag::Lf_Get, &httpRequest);
		if (1 == httpRequestRes)
		{
			return getBlob(httpRequest, autoRemoveRequest);
		}
	}
	return NULL;
}

int main()
{
    std::string token = "4f2dfa0dd904461aa65e53c2c1b49b15";
    std::string passid = "whscsyxgl";
    std::string url = "http://rio.wuhan.gov.cn/ebus/skdsj/ServiceAdapter/MAP/EMAP_WEB/" + token + "/tile/17/53835/107128";
    std::string nonce = Utility::GenerateGuid();
    std::string timestamp = std::to_string(Utility::GetCurTime());
    std::string signature;
    Utility::GetSHA256(signature, timestamp + token + nonce + timestamp);

    Enternity::Blob* blob = nullptr;

    HttpRequest* httpRequest  = new HttpRequest;
    httpRequest->m_strURL = url;
    auto b1 = Libcurl::GetInstance()->addHeader(httpRequest, "x-tif-nonce", nonce.c_str());
    auto b2 = Libcurl::GetInstance()->addHeader(httpRequest, "x-tif-signature", signature.c_str());
    auto b3 = Libcurl::GetInstance()->addHeader(httpRequest, "x-tif-timestamp", timestamp.c_str());
    auto b4 = Libcurl::GetInstance()->addHeader(httpRequest, "x-tif-paasid", passid.c_str());

    Libcurl::GetInstance()->get(httpRequest, true);

    std::cout << "request:" + url << std::endl;
    std::cout << httpRequest->m_curlList->data << std::endl;
    std::cout << httpRequest->m_curlList->next->data << std::endl;
    std::cout << httpRequest->m_curlList->next->next->data << std::endl;
    //std::cout << httpRequest->m_curlList->next->next->next->data << std::endl;
    std::cout << "result:" + std::to_string(httpRequest->m_status) << std::endl;
    int httpRequestRes = Libcurl::GetInstance()->getHttpRequest(url.c_str(), LibcurlFlag::Lf_Get, &httpRequest);
    if (1 == httpRequestRes)
    {
        blob = getBlob(httpRequest, true);
    }
    


	
	getchar();
	return 0;
}

