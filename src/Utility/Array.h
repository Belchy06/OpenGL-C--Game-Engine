#pragma once

#include <string>
#include <vector>
#include <initializer_list>

template <typename T>
class Array
{
public:
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

private:
	std::vector<T> Data;
};
