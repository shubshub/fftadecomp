#include "ffta.h"

/* Target 0x080254A0..0x08025560, 192 bytes (leaf, 17-entry jump table). */
typedef struct {
    u16 index;
    u8 unknown_02[2];
    u8 kind;
    u8 unknown_05[0x0F];
    s32 value_14;
    u8 unknown_18[0x468];
    u8 table_480[1];
} Context080254A0;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags_94;
} State080254A0;

extern Context080254A0 *data_0200F438;
extern State080254A0 g_state_0200F390;

s32 func_080254A0(void)
{
    u16 index;

    if (data_0200F438->kind == 0)
        return 0;
    index = data_0200F438->index - 1;
    switch (data_0200F438->kind) {
    case 4:
        return index + 7;
    case 1:
    case 5:
    case 17:
        return data_0200F438->table_480[index];
    case 10:
        return 10;
    case 11:
        return index + 0x12;
    case 3:
        return index;
    case 2:
    case 6:
    case 7:
    case 8:
    case 13:
    case 14:
        return data_0200F438->value_14;
    case 15:
        return (g_state_0200F390.flags_94 & 0x20) ? 0x21 : data_0200F438->value_14;
    default:
        return 0;
    }
}
