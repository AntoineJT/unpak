#include <iostream>
#include <filesystem>

// #define RT_ENSURE_PREFIX "Custom prefix: "

#include "cpak/pak.h"
#include "common/my_asserts.h"

int main()
{
	const std::string filename = "PAK0.PAK";
	std::cout << "Test with " << filename << std::endl;

	FILE* fp = fopen(filename.c_str(), "rb");
	RT_ENSURE(fp, "File '" + filename + "' not found!");

	auto pPak = pak_preload_files(fp);
	RT_ENSURE_BEGIN(pPak, filename + " must be a valid PAK file!")
		fclose(fp);
	RT_ENSURE_END()
	for (int i = 0; i < pPak->size; ++i) {
		auto pFile = pPak->files[i];
		// std::cout << pFile->name << "\n";
		auto filepath = std::filesystem::absolute(std::string("test/") + pFile->name);
		auto dirpath = filepath;
		dirpath.remove_filename();
		if (!std::filesystem::exists(dirpath)) {
			std::filesystem::create_directories(dirpath);
			// Don't know why but the return value of create_directories is silly
			RT_ENSURE(std::filesystem::exists(dirpath), "Failed to create directories (" + dirpath.string() + ")");
		}
		auto pCont = pak_get_file(fp, pFile);
		pak_write_content_to(filepath.string().c_str(), pCont);
		pak_destroy_pak_file_content_t(pCont);
	}
	pak_write_content_to("C:\\Fichiers\\GitHub\\pak-extractor\\test\\r_item1.wav", pak_get_file(fp, pPak->files[0]));
	fclose(fp);
	pak_destroy_pak_files_t(pPak);
}
