#ifndef CONTROLLER_INDEX_H
#define CONTROLLER_INDEX_H

#include <WebFile.h>
#include <Config.h>

namespace Angelsen
{
    struct ControllerIndex
    {
        ControllerIndex(const Config& config);

        std::string get();

        const Config& config_;
        EasyWeb::WebFile index_;
    };
}


#endif // CONTROLLER_INDEX_H
