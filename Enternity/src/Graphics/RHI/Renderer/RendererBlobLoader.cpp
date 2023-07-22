#include "RendererBlobLoader.h"
#include "Engine/Engine.h"
#include "Engine/Blob.h"
#include "Engine/BlobHolder.h"
#include "Engine/Log.h"
#include "RendererBlobHolder.h"
#include "Engine/NativeFileSystem.h"
#include <fstream>
#include <rapidjson/document.h>

namespace Enternity
{
	RendererBlobLoader::RendererBlobLoader() : BlobLoader("renderer://")
	{

	}

	void RendererBlobLoader::doLoad(BlobHolder* blobHolder)
	{
		if (blobHolder->getLoadingState() != BlobHolder::loading_state_pending)
			return;

		RendererBlobHolder* rendererBlobHolder = dynamic_cast<RendererBlobHolder*>(blobHolder);
		if (!rendererBlobHolder)
			return;

		m_mtx.lock();

		Blob* blob = nullptr;
		Engine::GetInstance().getNativeFileSystem()->read(blob, rendererBlobHolder->getPath());
		if (!blob)
		{
			rendererBlobHolder->loadFailed__();
			LOG_ERROR("Renderer load failed(read rdr file):{0}", rendererBlobHolder->getPath());
			m_mtx.unlock();
			return;
		}
		
		std::string jsonStr((char*)blob->getData(), blob->getLength());
		SAFE_DELETE_SET_NULL(blob);
		rapidjson::Document doc;
		if (doc.Parse(jsonStr.c_str()).HasParseError())
		{
			rendererBlobHolder->loadFailed__();
			LOG_ERROR("Renderer load failed(parse json file):{0}", rendererBlobHolder->getPath());
			m_mtx.unlock();
			return;
		}

		int offset = 0;
		Blob* vertBlob = nullptr;
		if (doc.HasMember("VertexShader") && doc["VertexShader"].IsString())
		{
			rendererBlobHolder->m_shaderTypes.insert(RendererBlobHolder::VertexShader);
			Engine::GetInstance().getNativeFileSystem()->read(vertBlob, doc["VertexShader"].GetString());
			if (vertBlob)
			{
				rendererBlobHolder->m_shaderDesc.vertDataOffset = offset;
				rendererBlobHolder->m_shaderDesc.vertDataSize = (unsigned int)vertBlob->getLength();
				offset += rendererBlobHolder->m_shaderDesc.vertDataSize;
			}
		}

		Blob* geomBlob = nullptr;
		if (doc.HasMember("GeometryShader") && doc["GeometryShader"].IsString())
		{
			rendererBlobHolder->m_shaderTypes.insert(RendererBlobHolder::GeometryShader);
			Engine::GetInstance().getNativeFileSystem()->read(geomBlob, doc["GeometryShader"].GetString());
			if (geomBlob)
			{
				rendererBlobHolder->m_shaderDesc.geomDataOffset = offset;
				rendererBlobHolder->m_shaderDesc.geomDataSize = (unsigned int)geomBlob->getLength();
				offset += rendererBlobHolder->m_shaderDesc.geomDataSize;
			}
		}

		Blob* fragBlob = nullptr;
		if (doc.HasMember("FragmentShader") && doc["FragmentShader"].IsString())
		{
			rendererBlobHolder->m_shaderTypes.insert(RendererBlobHolder::FragmentShader);
			Engine::GetInstance().getNativeFileSystem()->read(fragBlob, doc["FragmentShader"].GetString());
			if (fragBlob)
			{
				rendererBlobHolder->m_shaderDesc.fragDataOffset = offset;
				rendererBlobHolder->m_shaderDesc.fragDataSize = (unsigned int)fragBlob->getLength();
				offset += rendererBlobHolder->m_shaderDesc.fragDataSize;
			}
		}

		Blob* renderer = new Blob(offset);

		if (vertBlob)
		{
			memcpy_s((char*)renderer->getData() + rendererBlobHolder->m_shaderDesc.vertDataOffset,
				rendererBlobHolder->m_shaderDesc.vertDataSize, vertBlob->getData(), rendererBlobHolder->m_shaderDesc.vertDataSize);
		}

		if (geomBlob)
		{
			memcpy_s((char*)renderer->getData() + rendererBlobHolder->m_shaderDesc.geomDataOffset,
				rendererBlobHolder->m_shaderDesc.geomDataSize, geomBlob->getData(), rendererBlobHolder->m_shaderDesc.geomDataSize);
		}

		if (fragBlob)
		{
			memcpy_s((char*)renderer->getData() + rendererBlobHolder->m_shaderDesc.fragDataOffset,
				rendererBlobHolder->m_shaderDesc.fragDataSize, fragBlob->getData(), rendererBlobHolder->m_shaderDesc.fragDataSize);
		}

		SAFE_DELETE_SET_NULL(vertBlob);
		SAFE_DELETE_SET_NULL(geomBlob);
		SAFE_DELETE_SET_NULL(fragBlob);

		rendererBlobHolder->loadSucceeded__(renderer);


		m_mtx.unlock();
	}

	BlobHolder* RendererBlobLoader::createBlobHolder(const std::string& path)
	{
		return new RendererBlobHolder(this, path);
	}
}