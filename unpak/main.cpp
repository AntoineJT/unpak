#include <iostream>
#include <fstream>

#include "pakdef.h"

// Convert it to template?
#define ASSERT_ERR(x, msg) \
    if (!(x)) { \
        std::cerr << msg << std::endl; \
        exit(EXIT_FAILURE); \
    }

int main()
{
    // TODO Make that clean
    pak_header_t pakHeader;
    std::ifstream inputfile("PAK0.PAK", std::ios::binary);
    inputfile >> pakHeader.id >> pakHeader.offset >> pakHeader.size;

    const int filesCount = pakHeader.size / sizeof(pak_file_t);
    std::cout << "id: " << pakHeader.id
        << "; offset: " << pakHeader.offset
        << "; size: " << pakHeader.size
        << "; nb files: " << filesCount
        << std::endl;
    ASSERT_ERR(std::memcmp(pakHeader.id, "PACK", 4) == 0, "Invalid PAK file!");
}
