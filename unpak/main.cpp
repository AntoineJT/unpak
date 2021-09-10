#include <iostream>
#include <fstream>
#include <vector>

#include "pakdef.h"

// rt -> runtime
void rt_assert_err(bool cond, std::string msg)
{
    if (!cond) {
        std::cerr << msg << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main()
{
    // TODO Make that clean
    pak_header_t pakHeader;
    pakHeader.offset = 0;
    pakHeader.size = 0;
    std::ifstream inputfile("PAK0.PAK", std::ios::binary);
    // NOTE: Ensure platform is Little Endian or use a convert function here
    inputfile >> pakHeader.id
        >> pakHeader.offset
        >> pakHeader.size;

    const int filesCount = pakHeader.size / sizeof(pak_file_t);
    std::cout << "id: " << pakHeader.id
        << "; offset: " << pakHeader.offset
        << "; size: " << pakHeader.size
        << "; nb files: " << filesCount
        << std::endl;
    rt_assert_err(std::memcmp(pakHeader.id, "PACK", 4) == 0, 
        "Invalid PAK file! (" + std::string(pakHeader.id) + ")");

    if (pakHeader.offset > 0) {
        std::string padding(pakHeader.offset, '\0');
        inputfile.read(&padding[0], pakHeader.offset);
    }

    std::vector<pak_file_t> pakFileHeaders;
    pakFileHeaders.reserve(filesCount);
    for (int i = 0; i < filesCount; ++i) {
        pak_file_t pakFileHeader;
        pakFileHeader.offset = 0;
        pakFileHeader.size = 0;

        std::cout << inputfile.tellg() << std::endl;
        std::string er(54, '\0');
        inputfile.read(&er[0], 54);
        std::cout << er;
        // NOTE: Ensure platform is Little Endian or use a convert function here
        inputfile >> pakFileHeader.name
            >> pakFileHeader.offset
            >> pakFileHeader.size;
        std::cout << "name: " << pakFileHeader.name
            << "; offset: " << pakFileHeader.offset
            << "; size: " << pakFileHeader.size
            << std::endl;

        pakFileHeaders[i] = std::move(pakFileHeader);
    }
}
