#include "../BlobHolder.h"

namespace Enternity
{
	class ShaderBlobHolder : public BlobHolder
	{
	public:
		ShaderBlobHolder(const AssetID& assetID);
		virtual void doLoad() override;
	};
}