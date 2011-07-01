#ifndef __COMMON_DEFS_H
#define __COMMON_DEFS_H
#include <stdint.h>

#define TRUE  1
#define FALSE 0
#define UNUSED __attribute__((unused))
#define EXPECT(x,y) __builtin__expect((x),(y))
#define LIKELY(x) EXPECT((x),TRUE)
#define UNLIKELY(x) EXPECT((x),FALSE)

typedef uint8_t byte;

#endif
