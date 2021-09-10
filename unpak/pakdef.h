#pragma once
#include <stdint.h>

typedef struct
{
    char id[4]; // should be "PACK"
    int32_t offset;
    int32_t size;
} pak_header_t;

typedef struct
{
    char name[56];
    int32_t offset;
    int32_t size;
} pak_file_t;
