//
// Copyright (c) 2024-2030 Jiang. Xing
//
// Last Modified: 2024-03-03 01:04 AM
// VERSION: 1.0.0
#pragma once

#ifndef DI_CXX_VERSION_LIMIT
    #define DI_CXX_VERSION_LIMIT 202002L
#endif

#if defined(__GNUC__)
    #if (__cplusplus < DI_CXX_VERSION_LIMIT) || (__GNUC__ < 9) || (__GNUC_MINOR__ < 1)
        #error "ponder::di requires C++20 support GCC-9.1+"
    #endif
#elif defined(_MSC_VER)
    #if (_MSC_VER < 1900 || _MSVC_LANG < DI_CXX_VERSION_LIMIT)
        #error "ponder::di requires C++20 support MSVC-2017+"
    #endif
#elif defined(__CLANG__)
    #error "ponder::di not support clang."
#endif

#define PONDER_DI_VERSION_MAJOR 1
#define PONDER_DI_VERSION_MINOR 0
#define PONDER_DI_VERSION_PATCH 0

#define PONDER_DI_STRINGIFY(x) #x

#define PONDER_DI_VERSION_STRING_GET(major, minor, patch) PONDER_DI_STRINGIFY(major) "." PONDER_DI_STRINGIFY(minor) "." PONDER_DI_STRINGIFY(patch)
#define PONDER_DI_VERSION_VALUE_GET(major, minor, patch) ((major) * 10000 + (minor) * 100 + (patch))

#define PONDER_DI_VERSION_STRING PONDER_DI_VERSION_STRING_GET(PONDER_DI_VERSION_MAJOR, PONDER_DI_VERSION_MINOR, PONDER_DI_VERSION_PATCH)
#define PONDER_DI_VERSION PONDER_DI_VERSION_VALUE_GET(PONDER_DI_VERSION_MAJOR, PONDER_DI_VERSION_MINOR, PONDER_DI_VERSION_PATCH)

#ifndef PONDER_DI_HPP
#define PONDER_DI_HPP

template<typename T>
void print_type() {
    std::cout << typeid(T).name() << std::endl;
}

#endif //PONDER_DI_HPP
