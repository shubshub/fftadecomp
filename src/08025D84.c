#include "ffta.h"

typedef struct Entry08025D84 {
    u16 id;
    u16 unknown_02;
} Entry08025D84;

typedef struct Object08025D84 {
    u8 unknown_00[0x94];
    const Entry08025D84 *entries;
} Object08025D84;

extern u8 func_080CB99C(u16 id);

/* Complete [0x08025D84, 0x08025DAA): 38 bytes, 18 instructions. */
u32 func_08025D84(const Object08025D84 *object, u32 index)
{
    u16 entry_id = object->entries[index].id;
    u16 id = 0x18A;

    if (entry_id <= 0x55)
        id = 0x189;
    return func_080CB99C(id) + 13;
}
