/******************************************************************************
    An example to show how to use CAPI
    Copyright (C) 2014 Wang Bin <wbsecg1@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
******************************************************************************/
#define ZLIB_CAPI_BUILD
#define DEBUG ////log dll load and symbol resolve
//#define CAPI_IS_LAZY_RESOLVE 0 //define it will resolve all symbols in constructor
#ifndef CAPI_LINK_ZLIB
#include <QtCore/QLibrary> // need a library loader/resolver class whose function names like QLibrary
#include "capi.h"
#endif //CAPI_LINK_ZLIB
#include "zlib_api.h" //include last because zlib.h was in namespace capi to avoid covering types later

namespace zlib {
#ifdef CAPI_LINK_ZLIB
api::api(){dll=0;}
api::~api(){}
bool api::loaded() const { return true;}
#else
static const char* zlib[] = {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__)
    "zlib",
#else
    "z",
#endif
    NULL
};
static const int versions[] = { ::capi::NoVersion, 1, 0, ::capi::EndVersion };
//CAPI_BEGIN_DLL(zlib, QLibrary)
CAPI_BEGIN_DLL_VER(zlib, versions, QLibrary)
CAPI_DEFINE_ENTRY(const char*, zlibVersion, CAPI_ARG0())
CAPI_DEFINE_ENTRY(const char*, zError, CAPI_ARG1(int))
CAPI_END_DLL()
CAPI_DEFINE_DLL
CAPI_DEFINE(const char*, zlibVersion, CAPI_ARG0())
CAPI_DEFINE(const char*, zError, CAPI_ARG1(int))
#endif //CAPI_LINK_ZLIB
} //namespace zlib
