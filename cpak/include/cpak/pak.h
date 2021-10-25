#pragma once

#ifndef __cplusplus
#include <stdio.h>
#else
#include <cstdio>
#endif

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

typedef struct pak_file_content_s
{
	int size;
	void* content;
} pak_file_content_t;

pak_files_t* pak_preload_files(FILE* fp);
pak_file_content_t* pak_get_file(FILE* fp, const pak_file_t* file);
void pak_destroy_pak_files_t(pak_files_t* pak_files);
void pak_destroy_pak_file_content_t(pak_file_content_t* pak_file_content);
void pak_write_content_to(const char* path, const pak_file_content_t* content);

#ifdef __cplusplus
}
#endif
