#pragma once

#include <fstream>
#include <memory>

#include "File.hpp"

namespace BFCD
{
	class FileHandler
	{
	public:
		FileHandler();
		FileHandler(const std::string& filePath);
		FileHandler(FileHandler& fileHandler);
		FileHandler(FileHandler&& fileHandler) noexcept;
		~FileHandler() = default;

		inline std::shared_ptr<File> getFile() const { return m_File; }
		inline File* getFilePtr() const { return m_File.get(); }
		bool saveData(std::string& data); // returns true if data saved
		bool readData(); // return true if reads successfully

	private:
		std::shared_ptr<File> m_File;
	};
} // namespace: BFCD