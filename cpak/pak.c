// Based on a public domain
// implementation found at
// https://quakewiki.org/wiki/.pak
#include "include/cpak/pak.h"
#include "common/my_asserts.h"

#include <stdlib.h>
#include <string.h>

// TODO Implement LittleLong to convert endianness if needed
#define LittleLong(x) x

static inline void pak_destroy_pak_files_t_sz(pak_files_t* pak_files, const int size)
{
	for (int i = 0; i < size; ++i) {
		free(pak_files->files[i]);
	}
	free(pak_files);
}

pak_files_t* pak_preload_files(FILE* fp)
{
	if (!fp)
		return NULL;

	pak_header_t pak_header = { .offset = 0, .size = 0 };
	if (!fread(&pak_header, sizeof(pak_header), 1, fp))
		goto pak_error;
	if (memcmp(pak_header.id, "PACK", 4) != 0)
		goto pak_error;

	pak_header.offset = LittleLong(pak_header.offset);
	pak_header.size = LittleLong(pak_header.size);

	int num_files = pak_header.size / sizeof(pak_file_t);

	if (fseek(fp, pak_header.offset, SEEK_SET) != 0)
		goto pak_error;

	int index = 0; // keep track of it in case of failure
	pak_file_t** pak_files = malloc(num_files * sizeof(pak_file_t*));
	if (!pak_files)
		goto pak_error;
	for (; index < num_files; ++index)
	{
		pak_file_t* pak_file = malloc(sizeof(pak_file_t));
		if (!pak_file)
			goto pak_preload_error;
		if (!fread(pak_file, sizeof(pak_file_t), 1, fp)) {
			free(pak_file);
			goto pak_preload_error;
		}

		pak_file->offset = LittleLong(pak_file->offset);
		pak_file->size = LittleLong(pak_file->size);
		pak_files[index] = pak_file;
	}
	pak_files_t* pak_preload = malloc(sizeof(pak_files_t));
	pak_preload->files = pak_files;
	pak_preload->size = num_files;
	return pak_preload;

pak_preload_error:
	pak_destroy_pak_files_t_sz(pak_files, index + 1);

pak_error:
	fclose(fp);
	return NULL;
}

// will be used to read file from a specific pak file
pak_file_content_t* pak_get_file(FILE* fp, const pak_file_t* file, const char* filename)
{
	if (fseek(fp, file->offset, SEEK_SET) != 0)
		return NULL;

	pak_file_content_t* fcont = malloc(sizeof(pak_file_content_t));
	void* buffer = malloc(file->size);
	RT_ENSURE(buffer, "Memory allocation failed for in pak file reading (buffer)");
	RT_ENSURE(fcont, "Memory allocation failed for in pak file reading (fcont)");

	if (!fread(buffer, file->size, 1, fp)) {
		free(buffer);
		free(fcont);
		return NULL;
	}

	fcont->content = buffer;
	fcont->size = file->size;
	return fcont;
}

void pak_destroy_pak_files_t(pak_files_t* pak_files)
{
	pak_destroy_pak_files_t_sz(pak_files, pak_files->size);
}

void pak_destroy_pak_file_content_t(pak_file_content_t* pak_file_content)
{
	free(pak_file_content->content);
	free(pak_file_content);
}

// TODO move it to some util source file?
// TODO return a bool?
void pak_write_content_to(const char* path, const pak_file_content_t* content)
{
	FILE* fp = fopen(path, "wb");
	// TODO improve it by supporting varargs?
	RT_ENSURE(fp, "Failed to open '%s' file!", path);
	RT_ENSURE(fwrite(content->content, content->size, 1, fp) == 1, "Failed to write file '%s' on disk!", path);
	fclose(fp);
}
