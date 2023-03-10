#pragma once

namespace Enternity
{
	class Blob
	{
	public:
		Blob(size_t length);
		Blob(const Blob& blob);
		virtual ~Blob();
	public:
		inline void* getData();
		inline size_t getLength();
		inline void* getData() const;
		inline size_t getLength() const;

		void copyDataFrom(void* src);
	private:
		void* m_data{ nullptr };
		size_t m_length{ 0 };
	};

	inline void* Blob::getData()
	{
		return m_data;
	}

	inline size_t Blob::getLength()
	{
		return m_length;
	}

	inline void* Blob::getData() const
	{
		return m_data;
	}

	inline size_t Blob::getLength() const
	{
		return m_length;
	}

	class TextureBlob : public Blob
	{
	public:
		TextureBlob(size_t length) : Blob(length) {}
		virtual ~TextureBlob() = default;
	public:
		int m_width = -1;
		int m_height = -1;
		int m_channels = -1;
	};
}