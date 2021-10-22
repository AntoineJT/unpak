#pragma once

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

void* pak_load_file(const char* pak_filename, const char* filename, int* out_filesize);
