#include "unpak/pak.hpp"

#include <iostream>
#include <filesystem>
#include <string>

#include "cpak/pak.h"
#include "common/my_asserts.h"

#define RT_ENSURE_PREFIX "error@unpak: "

void Unpak::Pak::ExtractFileTo(const FILE* fp, const pak_files_t* pPak, const std::filesystem::path& destpath)
{
	using namespace std::string_literals;

	for (int i = 0; i < pPak->size; ++i) {
		const auto pFile = pPak->files[i];
		std::cout << "> " << pFile->name << "\n";
		const auto filepath = destpath / pFile->name;
		auto dirpath = filepath;
		dirpath.remove_filename();
		if (!std::filesystem::exists(dirpath)) {
			std::filesystem::create_directories(dirpath);
			// Don't know why but the return value of create_directories is silly
			RT_ENSURE(std::filesystem::exists(dirpath), "Failed to create directories (" + dirpath.string() + ")");
		}
		auto pCont = pak_get_file(fp, pFile);
		RT_ENSURE(pCont, "Unable to read inner file '"s + pFile->name + "'");
		pak_write_content_to(filepath.string().c_str(), pCont);
		pak_free_pak_file_content_t(pCont);
	}
}
