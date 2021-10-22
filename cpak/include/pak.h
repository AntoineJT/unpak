#pragma once

#include <stdio.h>

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

pak_files_t* pak_preload_files(const char* pak_filename);
void* pak_get_file(FILE* fp, pak_file_t* file, const char* filename);
