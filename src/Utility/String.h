#include <xlocale>
#include <sstream>
#include <algorithm>

class String
{
	static inline std::wstring Widen(const char* InStr)
	{
		const auto Length = strlen(InStr);

		std::wstring Result;
		Result.resize(Length);

		const auto& Facet = std::use_facet<std::ctype<wchar_t>>(std::wostringstream().getloc());
		std::transform(InStr, InStr + Length, Result.begin(), [&Facet](const char ch) {
			return Facet.widen(ch);
		});
		return Result;
	}
};