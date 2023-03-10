#include "zip.hpp"
#include "zip.hpp"

extern "C" {
    #include <zip.h>
}

#include <filesystem>
#include <fstream>

using namespace std;

Zip::Zip(const char* path) noexcept 
        : path(path) {
    if (!filesystem::exists(filesystem::path(path))) {
        zip_t* zip = zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
        zip_close(zip);
    }
}

Zip::Zip(const char* path, const Compression compressionLevel) noexcept 
        : path(path) {
    zip_t* zip = zip_open(path, static_cast<int>(compressionLevel), 'w');
    zip_close(zip);
}

set<string> Zip::entries(const bool withFolders) const noexcept {
    set<string> target;
    zip_t* zip = zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
    int i, n = zip_entries_total(zip);
    for (i = 0; i < n; ++i) {
        zip_entry_openbyindex(zip, i);
        const string name(zip_entry_name(zip));
        if (!zip_entry_isdir(zip) or withFolders) {
            target.insert(name);
        }
        zip_entry_close(zip);
    }
    zip_close(zip);
    return target;
}

std::string Zip::entry(const char* name) const noexcept {
    struct zip_t* zip = zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'r');
    zip_entry_open(zip, name);
    size_t bufferSize = zip_entry_size(zip);
    char* data;
    zip_entry_read(zip, (void**)&data, &bufferSize);
    zip_entry_close(zip);
    zip_close(zip);
    string buffer(data);
    return buffer;
}

void Zip::insert(const std::string& file) noexcept {
    const filesystem::path filePath(file);
    const string& fileName = filePath.filename().string();
    deleteEntry(fileName.c_str());
    zip_t* zip = zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
    zip_entry_open(zip, fileName.c_str());
    zip_entry_fwrite(zip, file.c_str());
    zip_entry_close(zip);
    zip_close(zip);
}

void Zip::insert(const std::string& entry, const char* text) noexcept {
    insert(entry, text, strlen(text));
}

void Zip::insert(const std::string& entry, const char* bytes, const size_t byteCount) noexcept {
    deleteEntry(entry.c_str());
    zip_t* zip = zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'a');
    zip_entry_open(zip, entry.c_str());
    zip_entry_write(zip, bytes, byteCount);
    zip_entry_close(zip);
    zip_close(zip);
}

void Zip::deleteEntry(const char* entry) noexcept {
    deleteEntries(set{string(entry)});
}

void Zip::deleteEntries(std::set<std::string> names) noexcept {
    const size_t bufferSize = names.size();
    char** buffer = new char*[bufferSize];
    char** it = buffer;
    for (string entry : names) {
        *it++ = entry.data();
    }
    deleteEntries(bufferSize, buffer);
    delete[] buffer;
}

void Zip::deleteEntries(const size_t count, char** names) noexcept {
    zip_t* zip = zip_open(path, ZIP_DEFAULT_COMPRESSION_LEVEL, 'd');
    zip_entries_delete(zip, names, count);
    zip_close(zip);
}

void Zip::extract(const std::string& entry) const noexcept {
    //
}

