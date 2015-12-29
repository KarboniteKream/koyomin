#ifndef _STDINT_H
#define _STDINT_H

#include <stddef.h>

typedef signed char int8_t;
typedef short int16_t;
typedef int int32_t;
#if __WORDSIZE == 64
typedef long int64_t;
#else
typedef long long int64_t;
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#if __WORDSIZE == 64
typedef unsigned long uint64_t;
#else
typedef unsigned long long uint64_t;
#endif

#if __WORDSIZE == 64
typedef long intmax_t;
typedef unsigned long uintmax_t;
#else
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
#endif

#endif
