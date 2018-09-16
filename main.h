
/*
 * Copyright (c) 2018 Kamila "Palaiologos" Szewczyk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 * 
 * It's using GNU C extensions. If you're not using GCC, define NOGNU.
 * Define LOGLEVEL to change default (4).
 * Level 1: Show nothing
 * Level 2: Show errors
 * Level 3: Show errors & warnings
 * Level 4: Show errors, warnings & debug
 * Level 5: Show errors, warnings, debug, and info.
 * 
 * I think about reordering debug and info, if you'll need it, make change in this file.
 */

#ifndef __MACROLOGGER_H__
#define __MACROLOGGER_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __GET_ERRNO__() (errno == 0 ? "None" : strerror(errno))

#ifdef NOGNU
    #define __func__ "?"
#endif

#ifndef LOGLEVEL
    #define LOGLEVEL 4
#endif

#if LOGLEVEL < 3
    #define NDEBUG 1
#endif

#ifdef NDEBUG
    #define log_debug(M, ...)
#else
    #ifdef LOG_NOANSI
        #define log_debug(M, ...) fprintf(stderr, "DEBUG " M " at %s (%s:%d) \n", ##__VA_ARGS__, __func__, __FILE__, __LINE__)
    #else
        #define log_debug(M, ...) fprintf(stderr, "\33[34mDEBUG\33[39m " M "  \33[90m at %s (%s:%d) \33[39m\n", ##__VA_ARGS__, __func__, __FILE__, __LINE__)
    #endif
#endif

#ifdef LOG_NOANSI
    #define log_err(M, ...) fprintf(stderr,  "ERROR " M " at %s (%s:%d) errno:%s\n", ##__VA_ARGS__, __func__, __FILE__, __LINE__, __GET_ERRNO__())
    #define log_warn(M, ...) fprintf(stderr, "WARN  " M " at %s (%s:%d) errno:%s\n", ##__VA_ARGS__, __func__, __FILE__, __LINE__, __GET_ERRNO__())
    #define log_info(M, ...) fprintf(stderr, "INFO  " M " at %s (%s:%d)\n", ##__VA_ARGS__, __func__, __FILENAME__, __LINE__)
#else
    #define log_err(M, ...) fprintf(stderr,  "\33[31mERROR\33[39m " M "  \33[90m at %s (%s:%d) \33[94merrno: %s\33[39m\n", ##__VA_ARGS__, __func__, __FILE__, __LINE__, __GET_ERRNO__())
    #define log_warn(M, ...) fprintf(stderr, "\33[91mWARN\33[39m  " M "  \33[90m at %s (%s:%d) \33[39m\n", ##__VA_ARGS__, __func__, __FILENAME__, __LINE__)
    #define log_info(M, ...) fprintf(stderr, "\33[32mINFO\33[39m  " M "  \33[90m at %s (%s:%d) \33[39m\n", ##__VA_ARGS__, __func__, __FILENAME__, __LINE__)
#endif

#if LOGLEVEL < 4
    #undef log_info
    #define log_info(M, ...)
#endif
#if LOGLEVEL < 2
    #undef log_warn
    #define log_warn(M, ...)
#endif
#if LOGLEVEL < 1
    #undef log_error
    #define log_error(M, ...)
#endif

#endif
