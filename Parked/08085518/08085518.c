#include "ffta.h"

/* Complete 0x08085518..0x08085558: 64 bytes, 27 instructions. */
typedef struct {
    u8 unknown_00[4];
    u16 value;
    u8 unknown_06[0x0e];
} RowEntry08085518;

typedef struct {
    u8 unknown_00[0x18];
    RowEntry08085518 *rows;
} RowResource08085518;

typedef struct {
    u8 unknown_00[0x18];
    u16 count;
    u16 selected;
} RowCursor08085518;

typedef struct {
    RowCursor08085518 cursor;
    u8 unknown_1c[0x34];
    RowResource08085518 *resource;
    u8 unknown_54[0x78];
} RowSlot08085518;

extern u8 *data_03002818;
extern u16 func_08017B68(RowCursor08085518 *cursor, u32 row);

u16 func_08085518(u32 index, u32 row)
{
    u8 *context = data_03002818;
    u32 offset = index * sizeof(RowSlot08085518);
    RowResource08085518 *resource =
        *(RowResource08085518 **)(context + 0x2d50 + offset);
    u16 selected = func_08017B68(
        (RowCursor08085518 *)(context + offset + 0x2d00), (s8)row);

    return resource->rows[selected].value;
}
