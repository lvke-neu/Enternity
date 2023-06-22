namespace Enternity
{
	class MeshAsset;
	class IndexBuffer
	{
	public:
		IndexBuffer(MeshAsset* meshAsset, unsigned int location);
		~IndexBuffer();
	public:
		void bind();
		void unbind();
		inline unsigned int getCount();
	private:
		unsigned int m_renderId;
		unsigned int m_count;
	};

	inline unsigned int IndexBuffer::getCount()
	{
		return m_count;
	}
}