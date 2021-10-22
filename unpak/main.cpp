#include <iostream>

#include "cpak/pak.h"
#include "common/my_asserts.h"

int main()
{
    const char* filename = "PAK0.PAK";
    std::cout << "Test with PAK0.PAK" << std::endl;

    FILE* fp = fopen(filename, "rb");
    auto pPak = pak_preload_files(fp);
    if (!pPak) {
        fclose(fp);
        RT_ASSERT(pPak, "PAK0.PAK must exists!"); // terminate prog
    }
    for (int i = 0; i < pPak->size; ++i) {
        auto pFile = pPak->files[i];
        std::cout << pFile->name << "\n";
    }
    fclose(fp);
}
