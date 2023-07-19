#pragma once

namespace Enternity
{
	class BlobHolder;
	class Asset
	{	
	public:
		Asset() = default;
		virtual ~Asset() = default;
	public:
		virtual void initialize(BlobHolder* blobHolder)  = 0;
	};

}