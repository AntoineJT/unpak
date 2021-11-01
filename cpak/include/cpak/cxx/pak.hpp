#pragma once

#include "../pak.h"
#include <cassert>
#include <string_view>

namespace CPak::Pak {
    class Files;

    class FileContent {
        const FILE* m_fp;
        pak_file_content_t* m_data;

    public:
        FileContent(const FILE* fp, const pak_file_t* pFile);
        ~FileContent();

        inline bool IsValid() const {
            return m_data != nullptr;
        }
        inline void WriteTo(const std::string_view path) const {
            pak_write_content_to(path.data(), m_data);
        }
    };
    
    class Files {
        const FILE* m_fp;
        pak_files_t* m_files;

    public:
        explicit Files(const FILE* fp);
        ~Files();

        inline bool IsValid() const {
            return m_files != nullptr;
        }
        inline size_t size() const {
            return m_files->size;
        }
        inline pak_file_t* GetFilePtr(const size_t index) const {
            assert(index < m_files->size);
            return m_files->files[index];
        }
        inline FileContent GetFileContent(const size_t index) const {
            return { m_fp, GetFilePtr(index) };
        }
    };
}
