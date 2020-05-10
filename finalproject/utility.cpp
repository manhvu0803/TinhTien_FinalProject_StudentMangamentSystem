#include "utility.h"

std::string tt::capitalize(std::string s)
{
    for (int i = 0, lim = s.size(); i < lim; ++i)
        s[i] = toupper(s[i]);
    return s;
}

