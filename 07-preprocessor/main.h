#ifndef main_h
#define main_h
//#pragma once

#include <iostream>

// define a symbolic constant
#define pi 3.14159265

// define a macro
#define mult_pi(m)  3.14159265 * m

//FILE* openfile(string filename) {
#   ifdef __WIN32__
    // Windows-specific stuff
        return (FILE*)win32_open(filename.c_str());
#   else
    // Linux specific stuff
    //    return open(filename.c_str());

#   endif
//}

#endif // main_h
