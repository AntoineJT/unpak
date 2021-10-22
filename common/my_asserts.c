#include "include/my_asserts.h"

#include <stdio.h>
#include <stdlib.h>

void c_rt_assert(const int b_cond, const char* cond, const char* msg, const int line, const char* file)
{
    if (!b_cond) {
        printf("assertion failed (%s@%d): "
            "\n\t%s"
            "\n>\t%s", file, line, msg, cond);
        exit(EXIT_FAILURE);
    }
}
