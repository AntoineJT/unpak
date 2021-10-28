#pragma once

#include <filesystem>
#include "cpak/pak.h"

namespace Unpak::Pak {
    void ExtractFileTo(const FILE* fp, const pak_files_t* pPak, const std::filesystem::path& destpath);
}
