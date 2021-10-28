#include <iostream>
#include <filesystem>
#include <string>

#include <tclap/CmdLine.h>

#include "cpak/pak.h"
#include "common/my_asserts.h"
#include "unpak/pak.hpp"

#define RT_ENSURE_PREFIX "error@cli: "

std::string GetExistingAbsFilePath(const std::string_view filename)
{
	const auto pakpath = std::filesystem::absolute(filename);
	RT_ENSURE(std::filesystem::exists(pakpath), "Specified pakfile does not exists!");
	return pakpath.string();
}

int main(const int argc, const char* argv[])
{
	TCLAP::CmdLine cmd("Quake PAK Extractor - by AntoineJT");
	TCLAP::UnlabeledValueArg<std::string> pakfileArg("pakfile", "PAK file to extract", true, "PAK0.PAK", "string");
	TCLAP::UnlabeledValueArg<std::string> destArg("dest", "Folder to extract to", true, ".", "string");
	cmd.add(pakfileArg).add(destArg);
	cmd.parse(argc, argv);

	const std::string filename = pakfileArg.getValue();
	std::string pakpathstr = GetExistingAbsFilePath(filename);

	FILE* fp = fopen(pakpathstr.c_str(), "rb");
	RT_ENSURE(fp, "File '" + filename + "' not found!");

	auto pPak = pak_preload_files(fp);
	RT_ENSURE_BEGIN(pPak, filename + " must be a valid PAK file!")
		fclose(fp);
	RT_ENSURE_END()

	const auto destpath = std::filesystem::absolute(destArg.getValue());
	std::cout << "Extracting '" << pakpathstr << "' to '" << destpath.string() << "'" << std::endl;
	Unpak::Pak::ExtractFileTo(fp, pPak, destpath);
	fclose(fp);
	pak_free_pak_files_t(pPak);
}
