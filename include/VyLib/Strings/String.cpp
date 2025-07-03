#include <string>
#include <codecvt>
#include <locale>
#include <iostream>
#include <cwchar>
#include <cstring>
#include <algorithm>
#include <charconv>

#include "VyLib/Strings/String.h"
#include "VyLib/Prerequisites.h"

namespace Vy
{
	Vector<String> StrUtil::Split(const String& str, char delim)
	{
		Vector<String> elems;

		cstring	cstr  = str.c_str();
		u32 strLength = (u32)str.length();
		u32 start     = 0;
		u32 end       = 0;

		while (end <= strLength)
		{
			while (end <= strLength)
			{
				if (cstr[end] == delim)
					break;

				end++;
			}

			elems.push_back(str.substr(start, end - start));
			start = end + 1;
			end	  = start;
		}

		return elems;
	}


	String StrUtil::WStringToString(const WString& wstring)
	{
		std::wstring wstr = wstring.c_str();
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
		return converter.to_bytes(wstr);
	}

	String StrUtil::WCharToString(wchar_t wch)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		return conv.to_bytes(wch);
	}


	WString StrUtil::StringToWString(const String& string)
	{
		std::string str = string.c_str();
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
		return converter.from_bytes(str);
	}

	CharPtr StrUtil::WCharToChar(wcstring wch)
	{
		// Count required buffer size (plus one for null-terminator).
		size_t size   = (wcslen(wch) + 1) * sizeof(wchar_t);
		CharPtr  buffer = new char[size];

#pragma warning(disable : 4996)
		std::wcstombs(buffer, wch, size);

		return buffer;
	}


	wcstring StrUtil::CharToWChar(cstring chr)
	{
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wideStr = converter.from_bytes(chr);

		wchar_t* wideStrCopy = new wchar_t[wideStr.size() + 1];
		wcscpy_s(wideStrCopy, wideStr.size() + 1, wideStr.c_str());

		return wideStrCopy;
	}

	String StrUtil::EncodeUTF8(wchar_t chr)
	{
		String utf8str;
		if (chr < 0x80)
		{
			utf8str.push_back(static_cast<char>(chr));
		}
		else if (chr < 0x800)
		{
			utf8str.push_back(static_cast<char>(0xC0 | (chr >> 6)));
			utf8str.push_back(static_cast<char>(0x80 | (chr & 0x3F)));
		}
		else if (chr < 0x10000)
		{
			utf8str.push_back(static_cast<char>(0xE0 | (chr >> 12)));
			utf8str.push_back(static_cast<char>(0x80 | ((chr >> 6) & 0x3F)));
			utf8str.push_back(static_cast<char>(0x80 | (chr & 0x3F)));
		}
		else
		{
			utf8str.push_back(static_cast<char>(0xF0 | (chr >> 18)));
			utf8str.push_back(static_cast<char>(0x80 | ((chr >> 12) & 0x3F)));
			utf8str.push_back(static_cast<char>(0x80 | ((chr >> 6) & 0x3F)));
			utf8str.push_back(static_cast<char>(0x80 | (chr & 0x3F)));
		}
		return utf8str;
	}


	String StrUtil::ReplaceAll(const String& str, const String& toReplace, const String& replacement)
	{
		if (toReplace.empty())
			return str;

		String fin       = str;
		size_t startPos  = 0;
		while ((startPos = fin.find(toReplace, startPos)) != std::string::npos)
		{
			fin.replace(startPos, toReplace.length(), replacement);
			startPos += replacement.length();
		}
		return fin;
	}
    
	f32 StrUtil::StringToFloat(const String& str, u32& outDecimals)
	{
		try
		{
			const String fin = StrUtil::ReplaceAll(str, ",", ".");
			std::size_t	 pos = fin.find('.');
			if (pos != std::string::npos)
				outDecimals = static_cast<u32>(fin.length() - pos - 1);

			return std::stof(fin);
		}
		catch (const std::exception& e)
		{
			// LINA_ERR("Exception: StringToFloat() string: {0} - decimals: {1} - {2}", str, outDecimals, e.what());
			return 0.0f;
		}
	}

	i32 StrUtil::StringToInt(const String& str)
	{
		try
		{
			return std::stoi(str);
		}
		catch (const std::exception& e)
		{
			// LINA_ERR("Exception: StringToInt() string: {0} - {1}", str, e.what());
			return 0;
		}
	}

	u64 StrUtil::StringToBigInt(const String& str)
	{
		try
		{
			return static_cast<u64>(std::stoull(str));
		}
		catch (const std::exception& e)
		{
			// LINA_ERR("Exception: StringToInt() string: {0} - {1}", str, e.what());
			return 0;
		}
	}

	String StrUtil::RemoveAllDotsExceptFirst(const String& str)
	{
		String      result = str;
		std::size_t pos	   = result.find('.'); // find the first dot

		// if there is a dot in the string
		if (pos != std::string::npos)
		{
			// remove all subsequent dots
			pos++; // start from the next character
			std::size_t next;
			while ((next = result.find('.', pos)) != std::string::npos)
			{
				result.erase(next, 1); // erase the dot
			}
		}

		return result;
	}

	String StrUtil::FixStringNumber(const String& str)
	{
		String copy = str;

		std::size_t dot = copy.find(".");

		if (dot != std::string::npos)
		{
			copy = RemoveAllDotsExceptFirst(copy);

			const i32 dotPos = static_cast<i32>(dot);
			const i32 sz	 = static_cast<i32>(copy.length());

			// If nothing exists after dot, insert 0.
			if (dotPos == sz - 1)
				copy.insert(dot + 1, "0");

			// If nothing exists before dot insert 0.
			if (dotPos == 0)
				copy.insert(0, "0");
		}

		return copy;
	}

	String StrUtil::FloatToString(f32 val, u32 decimals)
	{
		char buffer[32]; // Adjust size if needed.
		auto [ptr, ec] = std::to_chars(buffer, buffer + sizeof(buffer), val, std::chars_format::fixed, decimals);
		return (ec == std::errc()) ? std::string(buffer, ptr) : ""; // Handle errors (optional).
	}

	String StrUtil::GetUntilFirstOf(const String& str)
	{
		const size_t pos = str.find_first_of(str);

		if (pos == String::npos)
			return "";

		return str.substr(0, str.find_first_of(str));
	}

	Vector<String> StrUtil::SplitBy(const String& str, const String& splitStr)
	{
		// Split the path into directories
		Vector<String> directories;
		size_t		   start = 0, end = str.find(splitStr.c_str());
		while (end != String::npos)
		{
			const auto aq = str.substr(start, end - start);
			directories.push_back(aq);
			start = end + splitStr.size();
			end	  = str.find(splitStr.c_str(), start);
		}
		directories.push_back(str.substr(start));
		return directories;
	}

	String StrUtil::ToLower(const String& input)
	{
		String data = input;

		std::for_each(data.begin(), data.end(), [](char& c) { c = ::tolower(c); });

		return data;
	}

	String StrUtil::ToUpper(const String& input)
	{
		String data = input;

		std::for_each(data.begin(), data.end(), [](char& c) { c = ::toupper(c); });

		return data;
	}

	void StrUtil::SeperateByChar(const String& str, Vector<String>& out, char chr)
	{
		size_t start = 0;
		size_t end	 = str.find(chr);
		while (end != String::npos)
		{
			out.push_back(str.substr(start, end - start));
			start = end + 1;              // Move past the comma
			end	  = str.find(chr, start); // Find next comma
		}

		out.push_back(str.substr(start));
	}
	String StrUtil::SizeBytesToString(size_t sz, u32 decimals)
	{
		if (sz < 1000)
			return std::to_string(sz) + " b";

		if (sz < 1000000)
		{
			const f32 val = static_cast<f32>(sz) / 1000.0f;
			return FloatToString(val, decimals) + " kb";
		}

		const f32 val = static_cast<f32>(sz) / 1000000.0f;
		return FloatToString(val, decimals) + " mb";
	}

	String StrUtil::RemoveWhitespaces(const String& str)
	{
		std::string result;
		for (char c : str)
		{
			if (!std::isspace(static_cast<unsigned char>(c)))
			{
				result.push_back(c);
			}
		}
		return result;
	}
}