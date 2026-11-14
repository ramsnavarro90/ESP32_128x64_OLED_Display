#ifndef TYPEDEFS_H
#define TYPEDEFS_H

// Standard integer types
#include <stdint.h>
#include <stdbool.h>

// 1-bit types
typedef bool     u01;  // 1-bit unsigned integer
typedef bool     bit;  // 1-bit boolean, equivalent to u01

// 8-bit types
typedef uint8_t  u08;  // 8-bit unsigned integer
typedef int8_t   s08;  // 8-bit signed integer

// 16-bit types
typedef uint16_t u16;  // 16-bit unsigned integer
typedef int16_t  s16;  // 16-bit signed integer
typedef uint16_t W;    // Alias for 16-bit unsigned integer

// 32-bit types
typedef uint32_t u32;  // 32-bit unsigned integer
typedef int32_t  s32;  // 32-bit signed integer
typedef uint32_t DW;   // Alias for 32-bit unsigned integer

// 64-bit types
typedef uint64_t u64;  // 64-bit unsigned integer
typedef int64_t  s64;  // 64-bit signed integer
typedef uint64_t QW;   // Alias for 64-bit unsigned integer



#endif // TYPEDEFS_H