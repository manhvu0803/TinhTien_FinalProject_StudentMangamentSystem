#include "utility.h"
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

std::string tt::capitalize(std::string s)
{
    for (int i = 0, lim = s.size(); i < lim; ++i)
        s[i] = toupper(s[i]);
    return s;
}

int tt::makeFolder(std::string s)
{
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        return mkdir(s.c_str());
    #elif __APPLE__
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
            return 65;
        #elif TARGET_OS_IPHONE
            return 66;
        #elif TARGET_OS_MAC
            return mkdir(s.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
        #else
            #error "Unknown Apple platform"
        #endif
    #elif __linux__
        return mkdir(s.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
    #elif __unix__
        return 31;
    #elif defined(_POSIX_VERSION)
        return 32;
    #else
    #   error "Unknown compiler"
    #endif

    return 0;
}

bool tt::makeDir(std::string dir)
{
    bool created = false;
    size_t pos = dir.find('/', dir.find('/') + 1);
    while (pos < std::string::npos) {
        if (makeFolder(dir.substr(0, pos)) == 0) created = true;
        pos = dir.find('/', pos + 1);
    }
    return created;
}
