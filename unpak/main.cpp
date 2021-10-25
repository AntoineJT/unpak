#include <iostream>

// #define RT_ENSURE_PREFIX "Custom prefix: "

#include "cpak/pak.h"
#include "common/my_asserts.h"

int main()
{
	const std::string filename = "freedoom1.wad";
	std::cout << "Test with " << filename << std::endl;

	FILE* fp = fopen(filename.c_str(), "rb");
	RT_ENSURE(fp, "File '" + filename + "' not found!");

	auto pPak = pak_preload_files(fp);
	RT_ENSURE_BEGIN(pPak, filename + " must be a valid PAK file!")
		fclose(fp);
	RT_ENSURE_END()
	for (int i = 0; i < pPak->size; ++i) {
		auto pFile = pPak->files[i];
		std::cout << pFile->name << "\n";
	}
	pak_write_content_to("C:\\Fichiers\\GitHub\\pak-extractor\\test\\r_item1.wav", pak_get_file(fp, pPak->files[0]));
	fclose(fp);
	pak_destroy_pak_files_t(pPak);
}
