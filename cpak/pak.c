// Modified public domain unpak
// implementation found from
// https://quakewiki.org/wiki/.pak
#include "pak.h"

#include <stdlib.h>
#include <string.h>

// TODO Implement LittleLong to convert endianness if needed
#define LittleLong(x) x

#if 0
/* pak_filename : the os filename of the .pak file */
/* filename     : the name of the file you're trying to load from the .pak file (remember to use forward slashes for the path) */
/* out_filesize : if not null, the loaded file's size will be returned here */
/* returns a malloced buffer containing the file contents (remember to free it later), or NULL if any error occurred */
void* pak_load_file(const char* pak_filename, const char* filename, int* out_filesize)
{
  FILE* fp = fopen(pak_filename, "rb");
  if (!fp)
    return NULL;

  pak_header_t pak_header;
  if (!fread(&pak_header, sizeof(pak_header), 1, fp))
    goto pak_error;
  if (memcmp(pak_header.id, "PACK", 4) != 0)
    goto pak_error;

  pak_header.offset = LittleLong(pak_header.offset);
  pak_header.size = LittleLong(pak_header.size);

  int num_files = pak_header.size / sizeof(pak_file_t);

  if (fseek(fp, pak_header.offset, SEEK_SET) != 0)
    goto pak_error;

  pak_file_t pak_file;
  for (int i = 0; i < num_files; ++i)
  {
    if (!fread(&pak_file, sizeof(pak_file_t), 1, fp))
      goto pak_error;

    if (!strcmp(pak_file.name, filename))
    {
      pak_file.offset = LittleLong(pak_file.offset);
      pak_file.size = LittleLong(pak_file.size);

      if (fseek(fp, pak_file.offset, SEEK_SET) != 0)
        goto pak_error;

      void* buffer = malloc(pak_file.size);
      if (!buffer)
        goto pak_error;

      if (!fread(buffer, pak_file.size, 1, fp))
      {
        free(buffer);
        goto pak_error;
      }

      if (out_filesize)
        *out_filesize = pak_file.size;
      return buffer;
    }
  }

pak_error:
  fclose(fp);
  return NULL;
}
#endif

pak_files_t* pak_preload_files(const char* pak_filename)
{
  FILE* fp = fopen(pak_filename, "rb");
  if (!fp)
    return NULL;

  pak_header_t pak_header;
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
  for (; index < num_files; ++index)
  {
    pak_file_t* pak_file = malloc(sizeof(pak_file_t));
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
  for (int i = 0; i <= index; ++i) {
    free(pak_files[i]);
  }
  free(pak_files);

pak_error:
  fclose(fp);
  return NULL;
}

// TODO fonction qui liste les fichiers présents
// dans les différents .PAK

// will be used to read file from a specific pak file
void* pak_get_file(FILE* fp, pak_file_t* file, const char* filename)
{
  if (!strcmp(file->name, filename))
  {
    if (fseek(fp, file->offset, SEEK_SET) != 0)
      return NULL;

    void* buffer = malloc(file->size);
    if (!buffer)
      return NULL;

    if (!fread(buffer, file->size, 1, fp))
    {
      free(buffer);
      return NULL;
    }

    return buffer;
  }
}
