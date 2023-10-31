#include <fstream>
#include <memory>

#include "File.hpp"

namespace BFCD
{
	class Writer
	{
	public:
		Writer& operator=(const Writer& writer);
		Writer& operator=(Writer&& writer) noexcept;
		Writer(const Writer& writer);
		Writer(Writer&& writer) noexcept;
		Writer(const File& file);
		Writer(File&& file);
		Writer(std::string path);
		Writer(std::shared_ptr<File> file);

		inline std::shared_ptr<File> getFile() const { return m_File; }
		bool saveData(std::string data); // returns true if data saved

	private:
		std::shared_ptr<File> m_File;
	};
} // namespace: BFCD