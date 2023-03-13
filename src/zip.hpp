#pragma once

#include <string>
#include <set>

class Zip {
public:
	explicit Zip(const std::string& path) noexcept;

	std::set<std::string> getEntryNames() const noexcept;
	std::string getEntryData(const std::string& entryName) const noexcept;

private:
	const std::string& path;
};