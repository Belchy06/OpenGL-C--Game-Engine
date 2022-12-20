#pragma once

/**
 * Templated array class. Wraps a std::vector to provide some additional methods
 */

#include <string>
#include <vector>
#include <initializer_list>

template <typename T>
class Array
{
public:
	friend class Array;

	Array()
		: Data(std::vector<T>())
	{
	}

	Array(std::initializer_list<T> List)
		: Data(List)
	{
	}

	~Array()
	{
		Data.clear();
	}

	void Add(T InNewElement)
	{
		Data.push_back(InNewElement);
	}

	void Append(Array<T> InOther)
	{
		Data.insert(Data.end(), InOther.Data.begin(), InOther.Data.end());
	}

	T* GetData()
	{
		return Data.data();
	}

	size_t Length()
	{
		return Data.size();
	}

	template <typename T>
	void ForEach(T&& Visitor)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			Visitor(Data[i]);
		}
	}

	T& operator[](size_t InLocation)
	{
		return Data[InLocation];
	}

	void Reserve(size_t InNumElements)
	{
		Data.reserve(InNumElements);
	}

	void Assign(size_t InNumElements, const T& InValue)
	{
		Data.assign(InNumElements, InValue);
	}

private:
	std::vector<T> Data;
};
