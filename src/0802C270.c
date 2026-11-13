#include "ffta.h"

// Complete target [0x0802C270, 0x0802C398), 296 bytes.

typedef struct {
    u8 unknown_00[9];
    u8 level;
    u8 unknown_0A[0x10];
    u16 first;
    u8 unknown_1C[2];
    u16 second;
    u8 unknown_20[0xB6];
    u16 value;
} SourceObject0802C270;

typedef struct {
    u8 unknown_00[0xC];
    SourceObject0802C270 *object;
    u16 flags;
    u8 unknown_12[0x3D6];
    u8 value_digits[0x40];
    u8 level_digits[0x40];
    u8 first_digits[0x40];
    u8 second_digits[0x40];
    u8 first_bar[0x40];
    u8 unknown_528[0x40];
    u8 second_bar[0x40];
} Owner0802C270;

typedef struct {
    u8 unknown_00[0x1C];
} Entry0802BA08;

typedef struct TransferRecord TransferRecord;
typedef struct RequestNode RequestNode;

extern u8 *data_0200F440;
extern u8 g_state_020020D0[];
extern u8 data_060139A0[];
extern u8 data_060139C0[];
extern u8 data_06013AA0[];
extern u8 data_06013D40[];
extern Entry0802BA08 *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);
extern void func_0802BC7C(void *destination, u16 value, u16 base);
extern void func_0802BA40(Owner0802C270 *owner, SourceObject0802C270 *object,
                          u16 *query_first, u16 *query_second);
extern void func_0802BD90(void *destination, u16 value, u16 base);
extern void func_0802BEB0(void *destination, u16 value, u16 base, u16 tile,
                          u8 mode);
extern void func_0802BE40(const void *object);
extern void func_0802C008(u16 source_offset, u16 destination_offset);

void func_0802C270(Owner0802C270 *owner)
{
    u16 active = owner->flags & 0x10;
    u16 query_first;
    u16 query_second;
    u16 level_tile;
    u16 second_tile = 0x440;

    if (active)
        return;

    func_0802BC7C(owner->value_digits, owner->object->value, 0x260);
    func_0802BA40(owner, owner->object, &query_first, &query_second);
    func_0802BD90(owner->first_digits, query_first, 0x3A0);
    func_0802BC7C(owner->second_digits, query_second, 0x4C0);

    if (!g_state_020020D0[0xB5]) {
        func_08000ADC((TransferRecord *)func_0802BA08(), data_0200F440 + 0xBDC,
                      data_060139C0, 0x10);
        level_tile = 0x400;
        func_0802BC7C(owner->level_digits, owner->object->level, level_tile);
        func_08000B68((RequestNode *)func_0802BA08(), 0, (u32)data_060139A0, 8);
        func_08000B68((RequestNode *)func_0802BA08(), 0, (u32)data_06013AA0, 0x18);
        func_08000B68((RequestNode *)func_0802BA08(), 0, (u32)data_06013D40, 8);
    } else {
        func_0802C008(0x3E0, 0xA0);
        func_0802C008(0x3E0, 0x1A0);
        func_0802BEB0(owner->first_bar, owner->object->first, 0xC0, 0x400, 0);
        func_0802BEB0(owner->second_bar, owner->object->second, 0x1C0, second_tile, 1);
    }
    func_0802BE40(owner->object);
}
