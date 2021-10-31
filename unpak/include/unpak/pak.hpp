#pragma once

#include <filesystem>
#include "cpak/cxx/pak.hpp"

namespace Unpak::Pak {
    void ExtractFileTo(const FILE* fp, const CPak::Pak::Files& pak, const std::filesystem::path& destpath);
}
