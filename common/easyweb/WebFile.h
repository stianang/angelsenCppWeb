#ifndef WEBFILE_H
#define WEBFILE_H

#include <string>

namespace EasyWeb
{
    class WebFile
    {
    public:
        WebFile(const std::string filePath = "", bool reload = false);

        std::string& file();
        void read();
        void write(const std::string& filePath, const std::string &fileContent);

        void setFilePath(const std::string& path);
        void setReload(bool reload);

        std::string filePath();
        bool reload();

    protected:
        std::string filePath_{};
        bool reload_{false};

        std::string file_{};
    };
}



#endif // PAGE_H
