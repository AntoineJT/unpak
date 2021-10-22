#include "include/my_asserts.h"

#include <iostream>

void cpp_rt_assert(const bool b_cond, const char* cond, const char* msg, const int line, const char* file)
{
    if (!b_cond) {
        std::cerr << "assertion failed (" << file << "@" << line << "): "
                << "\n\t" << msg
                << "\n>\t" << cond << std::endl;
        exit(EXIT_FAILURE);
    }
}