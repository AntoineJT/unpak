// Modified public domain unpak
// implementation found from
// https://quakewiki.org/wiki/.pak
#include "pak.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO Implement LittleLong to convert endianness if needed
#define LittleLong(x) NULL

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