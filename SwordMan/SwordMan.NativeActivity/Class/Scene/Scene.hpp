/**
* @file Scene.hpp
* @brief Sceneで扱うクラス群です
* @author 日比野　真聖
* @date 2018/10/21
*/
#pragma once

#include <map>
#include <assert.h>
#include <iostream>


namespace Utility
{
	class Any final
	{
	public:
		explicit Any() noexcept
			: valueType(nullptr) {}
		template<typename ValueType>
		explicit Any(const ValueType& value) = delete;
		virtual ~Any() = default;
	public:
		template<typename ValueType>
		void SetValue(const ValueType& value)  noexcept
		{
			const ValueType* tmp = &value;
			valueType = const_cast<ValueType*>(tmp);
		}
		template<typename ValueType>
		void SetValue(const ValueType&& value) noexcept
		{
			const auto&& tmp = &value;
			valueType = std::move(const_cast<ValueType*>(tmp));
		}
		template<typename ValueType>
		void SetValuePtr(const ValueType& valuePtr) noexcept
		{
			valueType = (void*)valuePtr;
		}
		template<typename ValueType>
		ValueType* GetValue() const noexcept
		{
			return std::move(static_cast<ValueType*>(valueType));
		}
		template<typename ValueType>
		ValueType GetValuePtr() const noexcept
		{
			return static_cast<ValueType>(valueType);
		}
	private:
		void* valueType;
	};

	template<typename ValueType>
	inline const ValueType& Cast(const Any& any) noexcept
	{
		return std::move(*(any.GetValue<ValueType>()));
	}
	template<typename ValueType>
	inline const ValueType& CastPtr(const Any& any) noexcept
	{
		return any.GetValuePtr<ValueType>();
	}
}


class Parameter
{
public:
	Parameter() = default;
	~Parameter() = default;
	template<typename ValueType>
	void Set(const std::string& key, const ValueType& value) noexcept
	{
		map[key].SetValue(value);
	}
	template<typename ValueType>
	void SetPtr(const std::string& key, const ValueType& valuePtr) noexcept
	{
		map[key].SetValuePtr(valuePtr);
	}
	template<typename ValueType>
	const ValueType& Get(const std::string& key) const noexcept
	{
		auto it = map.find(key);
		if (map.end() == it)
		{
			std::cout << "キーのパラメータが存在しません";
			assert(false);
		}
		return Utility::Cast<ValueType>(it->second);
	}
	template<typename ValueType>
	const ValueType& GetPtr(const std::string& key) const noexcept
	{
		auto it = map.find(key);
		if (map.end() == it)
		{
			std::cout << "キーのパラメータが存在しません";
			assert(false);
		}
		return Utility::CastPtr<ValueType>(it->second);
	}
private:
	std::map<std::string, Utility::Any> map;
};
