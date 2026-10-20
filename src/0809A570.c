#include "ffta.h"

typedef struct {
    u8 unknown_00[0x44];
    u32 *primary;
    u32 unknown_48;
    u32 *additional[2];
} ObjectFlags;

void func_08021DE4(u32 *flags, u16 clear, u16 set);

void func_0809A570(void *object, u32 clear, u32 set)
{
    ObjectFlags *flags = object;
    u16 clearBits = clear;
    u16 setBits = set;
    s32 index;

    func_08021DE4(flags->primary, clearBits, setBits);
    for (index = 0; index < 2; index++) {
        if (flags->additional[index] != 0)
            func_08021DE4(flags->additional[index], clearBits, setBits);
    }
}
