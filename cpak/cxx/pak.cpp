#include "../include/cpak/cxx/pak.hpp"
#include <cassert>

CPak::Pak::Files::Files(const FILE* fp)
    : m_fp(fp)
    , m_files(pak_preload_files(fp))
{}

CPak::Pak::Files::~Files()
{
    pak_free_pak_files_t(m_files);
}

CPak::Pak::FileContent::FileContent(const FILE* fp, const pak_file_t* pFile)
     : m_fp(fp)
{
    m_data = pak_get_file(m_fp, pFile);
}

CPak::Pak::FileContent::~FileContent()
{
    pak_free_pak_file_content_t(m_data);
}
