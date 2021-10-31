#include "unpak/pak.hpp"

#include <iostream>
#include <filesystem>
#include <string>

#include "cpak/cxx/pak.hpp"
#include "common/my_asserts.h"

#define RT_ENSURE_PREFIX "error@unpak: "

void Unpak::Pak::ExtractFileTo(const FILE* fp, const CPak::Pak::Files& pak, const std::filesystem::path& destpath)
{
	using namespace std::string_literals;

	const size_t size = pak.size();
	for (int i = 0; i < size; ++i) {
		const auto pFile = pak.GetFilePtr(i);
		std::cout << "> " << pFile->name << "\n";
		const auto filepath = destpath / pFile->name;
		auto dirpath = filepath;
		dirpath.remove_filename();
		if (!std::filesystem::exists(dirpath)) {
			std::filesystem::create_directories(dirpath);
			// Don't know why but the return value of create_directories is silly
			RT_ENSURE(std::filesystem::exists(dirpath), "Failed to create directories (" + dirpath.string() + ")");
		}
		auto cont = CPak::Pak::FileContent(fp, pFile);
		RT_ENSURE(cont.IsValid(), "Unable to read inner file '"s + pFile->name + "'");
		cont.WriteTo(filepath.string());
	}
}
