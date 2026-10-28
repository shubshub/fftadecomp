#include "ffta.h"

typedef struct {
    u16 id;
    u16 unknown_02;
} Entry08025DAC;

typedef struct {
    u8 unknown_00[0x94];
    const Entry08025DAC *entries;
} Object08025DAC;

extern u8 func_080CB99C(u16 id);

/* 0x08025DAC - 26 bytes.
 * Target: 00b594300068890009180888a5f0f0fd0006000e0d3002bc0847
 */
u32 func_08025DAC(const Object08025DAC *object, u32 index)
{
    return func_080CB99C(object->entries[index].id) + 13;
}
