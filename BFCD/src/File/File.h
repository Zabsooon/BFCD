#pragma once

#include <iostream>
#include <memory>

#include <boost/iostreams/device/mapped_file.hpp>

namespace BFCD
{
	class File
	{
	public:
		typedef boost::iostreams::mapped_file::mapmode mapmode;
		typedef boost::iostreams::mapped_file::size_type size_type;
		typedef boost::intmax_t intmax_t;
		typedef boost::iostreams::mapped_file::iterator iterator;
		typedef boost::iostreams::mapped_file::const_iterator const_iterator;

		File()
			: m_MappedFile()
		{}

		explicit File(boost::iostreams::mapped_file_params File)
			: m_MappedFile(File)
		{}

		explicit File(const std::string& path,
                      mapmode mode = mapmode::readwrite,
                      size_type length = boost::iostreams::mapped_file::max_length,
                      intmax_t offset = boost::iostreams::mapped_file::alignment())
			: m_MappedFile(path, mode, length, m_MappedFile.alignment())
		{}

		File(const File& file)
			: m_MappedFile(file.m_MappedFile)
		{}

		File(File&& file) noexcept
			: m_MappedFile(std::move(file.m_MappedFile))
		{}

		void open(const std::string& path,
                  mapmode mode = mapmode::readwrite,
                  size_type length = boost::iostreams::mapped_file::max_length,
                  intmax_t offset = boost::iostreams::mapped_file::alignment())
		{
			m_MappedFile.open(path, mode, length, offset);
		}

		inline bool isOpen() const { return m_MappedFile.is_open(); }
		inline mapmode getMode() const { return m_MappedFile.flags(); }
		inline void close() { m_MappedFile.close(); }
		inline size_type getSize() const { return m_MappedFile.size(); }
		inline char* getData() const { return m_MappedFile.data(); }
		inline const char* getConstData() const { return m_MappedFile.const_data(); }
		inline iterator begin() const { return m_MappedFile.begin(); }
		inline const_iterator const_begin() const { return m_MappedFile.const_begin(); }
		inline iterator end() const { return m_MappedFile.end(); }
		inline const_iterator const_end() const { return m_MappedFile.const_end(); }
		inline static int alignment() { return boost::iostreams::mapped_file::alignment(); }

		~File()
		{
			m_MappedFile.close();
		}

	private:
		boost::iostreams::mapped_file m_MappedFile;
	};
}