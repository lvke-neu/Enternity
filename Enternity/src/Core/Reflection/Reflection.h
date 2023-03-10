#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

namespace Enternity
{
	template <typename T>
	class Reflection
	{
	private:
		Reflection() {}
		~Reflection() {}
		Reflection(const Reflection& rhs) {}
		Reflection& operator = (const Reflection& rhs) {}

	public:
		static Reflection<T>& getInstance()
		{
			static Reflection<T> instance;
			return instance;
		}


		T* createObject(const std::string& type)
		{
			auto it = m_classMap.find(type);
			if (it != m_classMap.end())
			{
				return (T*)(m_classMap[type]());
			}
			return nullptr;
		}


		void registerClass(const std::string& type, std::function<void*(void)> func)
		{
			m_classMap[type] = func;
		}


		std::vector<std::string> getTypes()
		{
			std::vector<std::string> types;
			for (auto it = m_classMap.begin(); it != m_classMap.end(); it++)
			{
				types.push_back(it->first);
			}
			return std::move(types);
		}

	private:
		std::map<std::string, std::function<void* (void)>> m_classMap;
	};

	template <typename T>
	class RegisterAction
	{
	public:
		RegisterAction(std::string type, std::function<void* (void)> func)
		{
			Reflection<T>::getInstance().registerClass(type, func);
		};
	};


#define REGISTER_CLASS(class_abstract, class_type, class_name) \
static RegisterAction<class_abstract> _register##class_name(class_type, [](){return new class_name;});

}

