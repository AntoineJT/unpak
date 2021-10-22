#include <iostream>

#include "pak.h"

#define RT_ASSERT(cond, msg) rt_assert((cond), #cond, (msg), __LINE__, __FILE__)

void rt_assert(const bool b_cond, const char* cond, const char* msg, const int line, const char* file)
{
    if (!b_cond) {
        std::cerr << "assertion failed (" << file << "@" << line << "): "
            << "\n\t" << msg
            << "\n>\t" << cond << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main()
{
    const char* filename = "PAK0.PAK";
    std::cout << "Test with PAK0.PAK" << std::endl;

    auto pPak = pak_preload_files(filename);
    RT_ASSERT(pPak, "PAK0.PAK must exists!");
    for (int i = 0; i < pPak->size; ++i) {
        auto pFile = pPak->files[i];
        std::cout << pFile->name << "\n";

    }
}
