#pragma once

#include <ostream>

#include "VyLib/Types/StringTypes.h"
#include "VyLib/Containers/Span.h"
#include "VyLib/Containers/Vector.h"
#include "VyLib/Containers/Map.h"
#include "VyLib/Serialization/Endianness.h"

namespace Vy
{
    class IStream
    {
    public:
        void Create(size_t size);
        void Create(u8* data, size_t size);
        void Create(const Span<u8>& span)
        {
            Create(span.data(), span.size());
        }

        void Destroy();

        void ReadFromIFStream(std::ifstream& stream);
        void ReadToRawEndianSafe(VoidPtr ptr, size_t size);
        void ReadToRaw(VoidPtr ptr, size_t size);
        void ReadToRaw(const Span<u8>& span)
        {
            ReadToRaw(span.data(), span.size());
        }   

        template <typename T>
        void Read(T& t)
        {
            memcpy(reinterpret_cast<u8*>(&t), &m_Data[m_Index], sizeof(T));
            m_Index += sizeof(T);
        }

        VYINLINE void SkipBy(size_t size)
        {
            m_Index += size;
        }

        VYINLINE void Seek(size_t index)
        {
            m_Index = index;
        }

		VYINLINE void Shrink(size_t size)
		{
			m_Size = size;
		}

        VYINLINE bool IsCompleted()
        {
            return m_Index >= m_Size;
        }

        VYINLINE bool Empty() const
        {
            return m_Size == 0;
        }

        VYINLINE size_t GetSize() const
        {
            return m_Size;
        }

		VYINLINE u8* GetDataRaw() const
		{
			return m_Data;
		}

		VYINLINE u8* GetDataCurrent()
		{
			return &m_Data[m_Index];
		}
    
    private:
        u8*    m_Data  = nullptr;
        size_t m_Index = 0;
        size_t m_Size  = 0;
    };


	// Helper traits to detect vector and hashmap
	template <typename T> 
    struct is_vector : std::false_type
	{
	};

	template <typename U> 
    struct is_vector<std::vector<U>> : std::true_type
	{
	};

	template <typename U> 
    struct is_vector<const std::vector<U>> : std::true_type
	{
	};

	template <typename T> 
    VYINLINE constexpr bool is_vector_v = is_vector<T>::value;

	template <typename T> 
    struct is_hashmap : std::false_type
	{
	};

	template <typename U, 
    typename V> struct is_hashmap<HashMap<U, V>> : std::true_type
	{
	};

	template <typename U, typename V> 
    struct is_hashmap<const HashMap<U, V>> : std::true_type
	{
	};

	template <typename T> 
    VYINLINE constexpr bool is_hashmap_v = is_hashmap<T>::value;

	template <typename Stream, typename U> 
    void SerializeVector(Stream& stream, Vector<U>& vec)
	{
		const u32 sz = static_cast<u32>(vec.size());
		stream << sz;

		if constexpr (std::is_pointer<U>::value)
		{
			for (auto item : vec)
				item->SaveToStream(stream);
		}
		else
		{
			for (auto& item : vec)
				stream << item;
		}
	}


	template <typename Stream, typename U> 
    void SerializeVector(Stream& stream, const Vector<U>& vec)
	{
		const u32 sz = static_cast<u32>(vec.size());
		stream << sz;

		if constexpr (std::is_pointer<U>::value)
		{
			for (auto item : vec)
				item->SaveToStream(stream);
		}
		else
		{
			for (const auto& item : vec)
				stream << item;
		}
	}


	template <typename Stream, typename U>
    void DeserializeVector(Stream& stream, Vector<U>& vec)
	{
		u32 sz = 0;
		stream >> sz;
		vec.resize(sz);
		if constexpr (std::is_pointer<U>::value)
		{
			for (u32 i = 0; i < sz; i++)
			{
				using UnderlyingType = typename std::remove_pointer<U>::type;
				vec[i]				 = new UnderlyingType();
				vec[i]->LoadFromStream(stream);
			}
		}
		else
		{
			for (u32 i = 0; i < sz; i++)
				stream >> vec[i];
		}
	}
    

	template <typename T> IStream& operator>>(IStream& stream, T& val)
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			stream.Read(val);
			if (Endianness::ShouldSwap())
			{
				Endianness::SwapEndian(val);
			}
		}
		else if constexpr (std::is_same_v<T, String> || std::is_same_v<T, std::string>)
		{
			u32 sz = 0;
			stream >> sz;
			VoidPtr d = malloc(sz);
			stream.ReadToRawEndianSafe(d, static_cast<size_t>(sz));
			String s((CharPtr)d, sz);
			val = s;
			free(d);
		}
		else if constexpr (std::is_enum_v<T>)
		{
			u8 ui8 = 0;
			stream >> ui8;
			val = static_cast<T>(ui8);
		}
		else if constexpr (is_vector_v<T>)
		{
			DeserializeVector(stream, val);
		}
		else if constexpr (is_hashmap_v<T>)
		{
			using KeyType	= typename T::key_type;
			using ValueType = typename T::mapped_type;
			DeserializeHashMap(stream, val);
		}
		else if constexpr (std::is_class_v<T>)
		{
			// Handle custom classes or structs
			val.LoadFromStream(stream);
		}
		else
		{
			assert(false);
		}

		return stream;
	}

    ///////////////////////////////////////////////////////////////////////////////////////////////

    class OStream
    {
	public:
		void CreateReserve(size_t size);

		void Destroy();
		
        void CheckGrow(size_t sz);
		
        void WriteToOFStream(std::ofstream& stream);
		void WriteRawEndianSafe(const u8* ptr, size_t size);
		void WriteRaw(const u8* ptr, size_t size);
		void WriteTo(Span<u8>& span);

		void WriteRaw(const Span<u8>& span)
		{
			WriteRaw(span.data(), span.size());
		}

		template <typename T> void Write(T& t)
		{
			if (m_Data == nullptr)
            {
                CreateReserve(sizeof(T));
            }

			u8*    ptr  = (u8*)&t;
			size_t size = sizeof(T);

			CheckGrow(size);
			memcpy(&m_Data[m_CurrentSize], ptr, size);
			m_CurrentSize += size;
		}

		VYINLINE size_t GetCurrentSize() const
		{
			return m_CurrentSize;
		}

		VYINLINE u8* GetDataRaw() const
		{
			return m_Data;
		}

		VYINLINE void Shrink(size_t size)
		{
			m_CurrentSize = size;
		}

	private:
		u8*    m_Data        = nullptr;
		size_t m_CurrentSize = 0;
		size_t m_TotalSize   = 0;
    };
    

	template <typename T> OStream& operator<<(OStream& stream, T& val)
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			auto copy = const_cast<typename std::remove_const<T>::type&>(val);
			if (Endianness::ShouldSwap())
				Endianness::SwapEndian(copy);
			stream.Write<T>(copy);
		}
		else if constexpr (std::is_same_v<T, String> || std::is_same_v<T, const String>)
		{
			const u32 sz = static_cast<u32>(val.size());
			stream << sz;
			stream.WriteRawEndianSafe((u8*)val.data(), val.size());
		}
		else if constexpr (std::is_enum_v<T>)
		{
			const u8 ui8 = static_cast<u8>(val);
			stream << ui8;
		}
		else if constexpr (is_vector_v<T>)
		{
			SerializeVector(stream, val);
		}
		else if constexpr (is_hashmap_v<T>)
		{
			using KeyType	= typename T::key_type;
			using ValueType = typename T::mapped_type;
			SerializeHashMap(stream, val);
		}
		else if constexpr (std::is_class_v<T>)
		{
			// Handle custom classes or structs
			val.SaveToStream(stream);
		}
		else
		{
			assert(false);
		}

		return stream;
	}

	template <typename T> OStream& operator<<(OStream& stream, T&& val)
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			auto copy = const_cast<typename std::remove_const<T>::type&>(val);
			if (Endianness::ShouldSwap())
            {
                Endianness::SwapEndian(copy);
            }
			stream.Write<T>(copy);
		}
		else if constexpr (std::is_same_v<T, String>)
		{
			const u32 sz = static_cast<u32>(val.size());
			stream << sz;
			stream.WriteRawEndianSafe((u8*)val.data(), val.size());
		}
		else if constexpr (std::is_enum_v<T>)
		{
			const u8 ui8 = static_cast<u8>(val);
			stream << ui8;
		}
		else if constexpr (is_vector_v<T>)
		{
			// Handle vector
			const u32 sz = static_cast<u32>(val.size());
			stream << sz;
			for (const auto& item : val)
				stream << val;
		}
		else if constexpr (is_hashmap_v<T>)
		{
			// Handle hashmap
			const u32 sz = static_cast<u32>(val.size());
			stream << sz;

			for (const auto& [key, value] : val)
			{
				stream << key;
				stream << val;
			}
		}
		else if constexpr (std::is_class_v<T>)
		{
			// Handle custom classes or structs
			val.SaveToStream(stream);
		}
		else
		{
			assert(false);
		}

		return stream;
	}



    ///////////////////////////////////////////////////////////////////////////////////////////////
    
    class RawStream
    {
	public:
		RawStream() : m_Data({}){};
		RawStream(const RawStream& other) = delete;

		~RawStream()
		{
		}

		void Create(OStream& stream);
		void Create(const Span<u8>& sp);
		void Create(u8* data, size_t size);
		void Destroy();

		VYINLINE Span<u8> GetSpan()
		{
			return m_Data;
		}

		VYINLINE u8* GetRaw() const
		{
			return m_Data.data();
		}

		VYINLINE size_t GetSize() const
		{
			return m_Data.size();
		}

		bool IsEmpty() const
		{
			return m_Data.empty();
		}

		void SaveToStream(OStream& stream) const;
		void LoadFromStream(IStream& stream);

	private:
		Span<u8> m_Data;
    };
}