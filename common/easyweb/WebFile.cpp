#include "WebFile.h"
#include <iostream>
#include <fstream>

using namespace EasyWeb;

WebFile::WebFile(const std::string filePath, bool reload)
    : filePath_{filePath},
      reload_{reload}
{

}

std::string& WebFile::file()
{
    if (file_.empty())
    {
        read();
    }
    else if (reload_)
    {
        read();
    }

    return file_;
}

void WebFile::read()
{
    file_.clear();
    std::ifstream file(filePath_);

    if (file.is_open())
    {
      std::string line;

      while ( getline (file, line) )
      {
          file_ += line;
      }
      file.close();
    }
    else
    {
        std::cerr << "Failed to open file: " << filePath_ << std::endl;
    }
}

void WebFile::write(const std::string& filePath, const std::string& fileContent)
{
    std::ofstream ofs;
    ofs.open(filePath, std::ofstream::out | std::ofstream::trunc);
    ofs << fileContent;
    ofs.close();
}

void WebFile::setFilePath(const std::string &path)
{
    filePath_ = path;
}

void WebFile::setReload(bool reload)
{
    reload_ = reload;
}

std::string WebFile::filePath()
{
    return filePath_;
}

bool WebFile::reload()
{
    return reload_;
}
