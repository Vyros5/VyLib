#include "VyLib/IO/Streams.h"

#include <fstream>
#include <algorithm>

namespace Vy
{
	void IStream::Create(size_t size)
	{
		Destroy();
		m_Data  = new u8[size];
		m_Index = 0;
		m_Size  = size;
	}

	void IStream::Create(u8* data, size_t size)
	{
		Destroy();
		const size_t unaligned = size;
		m_Data                 = new u8[size];

		memcpy(m_Data, data, unaligned);
		m_Index = 0;
		m_Size	= size;
	}

	void IStream::Destroy()
	{
		if (m_Data == nullptr)
			return;

		delete[] m_Data;

		m_Index = 0;
		m_Size	= 0;
		m_Data	= nullptr;
	}

	void IStream::ReadFromIFStream(std::ifstream& stream)
	{
		stream.read((CharPtr)m_Data, m_Size);
	}

	void IStream::ReadToRawEndianSafe(VoidPtr ptr, size_t size)
	{
		if (Endianness::ShouldSwap())
		{
			u8* data = &m_Data[m_Index];
			Vector<u8> v;

			v.insert(v.end(), data, data + size);

			Vector<u8> v2;
			v2.resize(v.size());
			std::reverse_copy(v.begin(), v.end(), v2.begin());

			memcpy(ptr, v2.data(), size);

			v.clear();
			v2.clear();
		}
		else
			memcpy(ptr, &m_Data[m_Index], size);

		m_Index += size;
	}

	void IStream::ReadToRaw(VoidPtr ptr, size_t size)
	{
		memcpy(ptr, &m_Data[m_Index], size);
		m_Index += size;
	}


    ///////////////////////////////////////////////////////////////////////////////////////////////


	void OStream::CreateReserve(size_t size)
	{
		m_Data        = new u8[size];
		m_TotalSize   = size;
		m_CurrentSize = 0;
	}

	void OStream::Destroy()
	{
		delete[] m_Data;

		m_CurrentSize = 0;
		m_TotalSize	  = 0;
		m_Data        = nullptr;
	}

	void OStream::WriteRawEndianSafe(const u8* ptr, size_t size)
	{
		if (m_Data == nullptr)
			CreateReserve(size);

		CheckGrow(size);

		if (Endianness::ShouldSwap())
		{
			Vector<u8> v;
			v.insert(v.end(), ptr, (ptr) + size);

			Vector<u8> v2;
			v2.resize(v.size());
			std::reverse_copy(v.begin(), v.end(), v2.begin());
			memcpy(&m_Data[m_CurrentSize], v2.data(), size);

			v.clear();
			v2.clear();
		}
		else
			memcpy(&m_Data[m_CurrentSize], ptr, size);

		m_CurrentSize += size;
	}

	void OStream::WriteRaw(const u8* ptr, size_t size)
	{
		if (m_Data == nullptr)
			CreateReserve(size);

		CheckGrow(size);
		memcpy(&m_Data[m_CurrentSize], ptr, size);
		m_CurrentSize += size;
	}

	void OStream::WriteTo(Span<u8>& span)
	{
		span = {new u8[m_CurrentSize], m_CurrentSize};
		memcpy(span.data(), GetDataRaw(), m_CurrentSize);
	}

	void OStream::CheckGrow(size_t sz)
	{
		if (m_CurrentSize + sz > m_TotalSize)
		{
			m_TotalSize	   = static_cast<size_t>((static_cast<float>(m_CurrentSize + sz) * 2.0f));
			u8* newData = new u8[m_TotalSize];
			memcpy(newData, m_Data, m_CurrentSize);
			delete[] m_Data;
			m_Data = newData;
		}
	}

	void OStream::WriteToOFStream(std::ofstream& stream)
	{
		stream.write((CharPtr)m_Data, m_CurrentSize);
	}


    ///////////////////////////////////////////////////////////////////////////////////////////////

    
	void RawStream::Create(const Span<u8>& sp)
	{
		Destroy();
		m_Data = {new u8[sp.size()], sp.size()};
		memcpy(m_Data.data(), sp.data(), sp.size());
	}

	void RawStream::Create(u8* data, size_t size)
	{
		Destroy();
		m_Data = {new u8[size], size};
		memcpy(m_Data.data(), data, size);
	}

	void RawStream::Create(OStream& stream)
	{
		Destroy();
		m_Data = {new u8[stream.GetCurrentSize()], stream.GetCurrentSize()};
		memcpy(m_Data.data(), stream.GetDataRaw(), stream.GetCurrentSize());
	}

	void RawStream::Destroy()
	{
		if (IsEmpty())
			return;
		delete[] m_Data.data();
		m_Data = {};
	}

	void RawStream::SaveToStream(OStream& stream) const
	{
		const u32 sz = static_cast<u32>(m_Data.size());
		stream << sz;
		if (sz != 0)
			stream.WriteRaw(m_Data);
	}

	void RawStream::LoadFromStream(IStream& stream)
	{
		u32 size = 0;
		stream >> size;
		if (size != 0)
		{
			const size_t sz = static_cast<size_t>(size);
			Destroy();
			m_Data = {new u8[sz], sz};
			stream.ReadToRaw(m_Data);
		}
	}
}