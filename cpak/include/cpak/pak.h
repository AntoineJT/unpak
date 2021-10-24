#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef struct pak_header_s
{
  char id[4];
  int offset;
  int size;
} pak_header_t;

typedef struct pak_file_s
{
  char name[56];
  int offset;
  int size;
} pak_file_t;

typedef struct pak_files_s
{
  int size;
  pak_file_t** files;
} pak_files_t;

pak_files_t* pak_preload_files(FILE* fp);
void* pak_get_file(FILE* fp, const pak_file_t* file);
void pak_destroy_pak_files_t(pak_files_t* pak_files);

#ifdef __cplusplus
}
#endif
