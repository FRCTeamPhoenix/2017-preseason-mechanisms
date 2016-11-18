#include "FileStream.h"

FileStream::FileStream(std::string filename)
    : fstream(filename)
{
}

FileStream::~FileStream(void)
{
    this->close();
}
