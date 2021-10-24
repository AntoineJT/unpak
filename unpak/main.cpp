#include <iostream>

#include "cpak/pak.h"
#include "common/my_asserts.h"

int main()
{
    const char* filename = "PAK0.PAK";
    std::cout << "Test with " << filename << std::endl;

    FILE* fp = fopen(filename, "rb");
    RT_ENSURE(fp, "File not found!");

    auto pPak = pak_preload_files(fp);
    if (!pPak) {
        fclose(fp);
        RT_ASSERT(pPak, "PAK0.PAK must be a valid PAK file!"); // terminate prog
    }
    for (int i = 0; i < pPak->size; ++i) {
        auto pFile = pPak->files[i];
        std::cout << pFile->name << "\n";
    }
    fclose(fp);
    pak_destroy_pak_files_t(pPak);
}
