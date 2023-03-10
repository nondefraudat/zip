#pragma once

#include <set>
#include <string>

class Zip {
public:

	enum class Compression : int {
		UNCOMPRESSED = 0,
		FASTEST = 1,
		FAST = 3,
		NORMAL = 5,
		MAXIMUM = 7,
		ULTRA = 9
	};

	explicit Zip(const char* path) noexcept;
	explicit Zip(const char* path, const Compression compression) noexcept;

	std::set<std::string> entries(const bool withFolders = false) const noexcept;
	std::string entry(const char* name) const noexcept;

	void insert(const std::string& file) noexcept;
	void insert(const std::string& entry, const char* text) noexcept;
	void insert(const std::string& entry, const char* bytes, const size_t byteCount) noexcept;

	void deleteEntry(const char* name) noexcept;
	void deleteEntries(std::set<std::string> names) noexcept;
	void deleteEntries(const size_t count, char** names) noexcept;

	void extract(const std::string& entry) const noexcept;

private:
	const char* path;
};
