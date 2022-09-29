#ifndef __PROJECTS_TGG_WORKING_DIR_HPP__
#define __PROJECTS_TGG_WORKING_DIR_HPP__

#ifdef MACOS
#include "CoreFoundation/CoreFoundation.h"
#endif

#include <string>


class WorkingDirectory
{
private:
    std::string path_;
  
public:
    WorkingDirectory();
  
    inline const std::string& Get() { return path_; }
};

#endif
