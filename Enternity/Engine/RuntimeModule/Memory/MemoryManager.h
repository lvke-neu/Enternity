#pragma once

#include "RuntimeModule/Interface/IRuntimeModule.h"
#include "Allocator.h"
#include <new>

namespace Enternity
{
	class MemoryManager : public IRuntimeModule
	{
	public:
		virtual ~MemoryManager() = default;

		virtual bool Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
	public:
		template<typename T, typename... Arguments>
		T* New(Arguments... parameters)
		{
			return new (Allocate(sizeof(T))) T(parameters...);
		}

		template<typename T>
		void Delete(T *p)
		{
			reinterpret_cast<T*>(p)->~T();
			Free(p, sizeof(T));
		}
		void* Allocate(size_t size);
		void  Free(void* p, size_t size);
	private:
		static size_t*        m_pBlockSizeLookup;
		static Allocator*     m_pAllocators;
	private:
		static Allocator* LookUpAllocator(size_t size);
	};
}