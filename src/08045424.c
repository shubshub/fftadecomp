#include "ffta.h"

struct Entry08045424 {
    u8 unknown_00[6];
    u8 selector;
    u8 unknown_07[5];
};

struct Record08045424 {
    u8 unknown_00;
    u8 unknown_08 : 5;
    u8 value : 8;
    u8 unknown_15 : 3;
    u8 unknown_03[24];
} __attribute__((packed));

extern const struct Entry08045424 g_table_08563A70[];
extern const struct Record08045424 g_table_08564670[];
extern u32 func_08036330(u8);

/* Target: [0x08045424, 0x08045482), 94 bytes, 41 instructions. */
u8 func_08045424(u8 index)
{
    u8 value = g_table_08564670[g_table_08563A70[index].selector].value;
    s32 result;

    if (value == 0)
        return 0xff;
    if (value & 0x80)
        result = value + 0x7f;
    else
        result = func_08036330(value) - 1;
    return result;
}
