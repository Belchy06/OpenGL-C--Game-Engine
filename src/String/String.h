#pragma once

#include <string>
#include <vector>

namespace String
{
	inline std::vector<std::string> Split(std::string InString, std::string InToken)
	{
		std::vector<std::string> Result;
		while (InString.size())
		{
			int Index = InString.find(InToken);
			if (Index != std::string::npos)
			{
				Result.push_back(InString.substr(0, Index));
				InString = InString.substr(Index + InToken.size());
				if (!InString.size())
				{
					Result.push_back(InString);
				}
			}
			else
			{
				Result.push_back(InString);
				InString = "";
			}
		}
		return Result;
	}
} // namespace String