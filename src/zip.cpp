#include "zip.hpp"

extern "C" {
	#include "zip.h"
}

using namespace std;

Zip::Zip(const string& path) noexcept 
		: path(path) { }

set<string> Zip::getEntryNames() const noexcept {
	set<string> entryNames;
	
	zip_t* zip = zip_open(this->path.c_str(), NULL, 'r');
	if (!zip) {
		return entryNames;
	}

	int entriyCount = zip_entries_total(zip);
	if (entriyCount <= 0) {
		zip_close(zip);
		return entryNames;
	}

	for (int i = 0; i < entriyCount; i++) {
		if (zip_entry_openbyindex(zip, i) < 0) {
			continue;
		}
		const string entryName(zip_entry_name(zip));
		entryNames.insert(entryName);
		zip_entry_close(zip);
	}

	zip_close(zip);
	return entryNames;
}

#include <iostream>

string Zip::getEntryData(const std::string& entryName) const noexcept {
	zip_t* zip = zip_open(this->path.c_str(), NULL, 'r');
	if (!zip) {
		return string();
	}

	if (zip_entry_open(zip, entryName.c_str()) < 0) {
		zip_close(zip);
		return string();
	}

	void* buffer;
	size_t bufferSize;
	if (zip_entry_read(zip, &buffer, &bufferSize) < 0) {
		zip_close(zip);
		return string();
	}
	zip_entry_close(zip);
	string entryData(reinterpret_cast<const char*>(buffer), bufferSize);
	free(buffer);
	
	zip_close(zip);
	return entryData;
}
