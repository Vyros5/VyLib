#pragma once

#include "VyLib/Containers/Vector.h"
#include "VyLib/Types/StringTypes.h"

namespace Vy
{
    class StrUtil
    {
    public:

        static Vector<String> Split(const String& str, char delim);

        static String	WStringToString(const WString& wstring);
        static WString	StringToWString(const String& string);

        static String	WCharToString(wchar_t wch);
        static String	EncodeUTF8(wchar_t wch);

        
        static String	FloatToString(f32 val, u32 decimals);
        static f32	    StringToFloat(const String& str, u32& outDecimals);
        
        static i32		StringToInt(const String& str);
        static u64		StringToBigInt(const String& str);
        
        static CharPtr	WCharToChar(wcstring wch);
        static wcstring CharToWChar(cstring chr);
        
        static String	ToUpper(const String& str);
        static String	ToLower(const String& str);
        
        static String	RemoveAllDotsExceptFirst(const String& str);
        static String	FixStringNumber(const String& str);
        static String	ReplaceAll(const String& str, const String& toReplace, const String& replacement);
        static String	GetUntilFirstOf(const String& str);

        static void		SeperateByChar(const String& str, Vector<String>& out, char chr);
        static String	SizeBytesToString(size_t sz, u32 decimals);
        static String	RemoveWhitespaces(const String& str);

        /**
         * @brief Returns a list of strings that fall in between each of the split string.
         * e.g. given a filesystem path will return a list of all directories in the path and the last file if there is one.
         */
        static Vector<String> SplitBy(const String& str, const String& splitStr);
    };
}