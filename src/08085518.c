#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 count;
    u16 scroll;
    u32 unknown_1C;
} Menu08085518;

typedef struct {
    u8 unknown_00[4];
    u16 field_04;
    u8 unknown_06[0xE];
} Entry08085518;

typedef struct {
    u8 unknown_00[0x18];
    Entry08085518 *entries;
} Object08085518;

typedef struct {
    u8 unknown_00[0x78];
    Menu08085518 menu;
    u8 unknown_98[0x30];
    Object08085518 *object;
} Slot08085518;

typedef struct {
    u8 unknown_0000[0x2C88];
    Slot08085518 slots[0];
} State08085518;

extern State08085518 *data_03002818;
extern u16 func_08017B68(Menu08085518 *menu, u32 row);

/* Complete target [0x08085518, 0x08085558): 64 bytes, 27 instructions.
 * 10b50d4a1368cc2250430c4c1a1912181468c018b422920180180906091692f717fb
 * 0004000ca2698100091889008918888810bc02bc084718280003502d0000
 */
u16 func_08085518(u32 index, s8 row)
{
    Object08085518 *object = data_03002818->slots[index].object;
    u16 selected = func_08017B68(&data_03002818->slots[index].menu, row);

    return object->entries[selected].field_04;
}
