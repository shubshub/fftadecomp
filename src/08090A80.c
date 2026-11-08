#include "ffta.h"

typedef struct {
    const void *data;
    u16 tile;
    u16 count;
    u32 unknown_08;
} Definition;

typedef struct {
    const void *data;
    u32 unknown_04;
    u16 tile;
    u8 unknown_0A;
    u8 count;
    u32 unknown_0C;
} DisplayEntry;

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

typedef struct ExtendedRequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u16 field_10;
    u16 field_12;
    u16 field_14;
    u8 unknown_16[2];
    struct ExtendedRequestNode *next;
} ExtendedRequestNode;

typedef struct {
    u8 *first;
    u8 *second;
    const Definition *definitions;
    DisplayEntry entries[14];
    u8 unknown_EC[0x164];
    TransferRecord transfers[2];
    ExtendedRequestNode request;
} DisplayState;

typedef struct {
    u8 unknown_00[0x14];
    u8 *destination;
} TransferState;

typedef struct {
    u16 display;
} ControlFlags;

typedef struct {
    u32 value : 8;
} ByteSetting;

typedef void (*BufferCopier)(void *, const void *, u32);
extern ByteSetting data_0200F49C;
extern u8 data_0200F498;
extern ByteSetting data_0200F4A0;
extern ByteSetting data_0200F4A4;
extern const Definition data_083941E0[];
extern const u8 data_083BF308[];
extern const u8 data_083C05E8[];
extern u8 data_06013C00[];
extern u8 data_06009C00[];
extern const u8 data_083C3864[];
extern TransferState data_030008B0;
extern BufferCopier data_0836D4BC;
extern u8 data_03003B20[];
extern ControlFlags g_control_flags_03000940;
extern void *func_08022840(u32 size);
extern s32 func_08005318(const void *, u8 *, u16, u16);
extern void func_08000A98(TransferRecord *, const void *, void *, u16);
extern void func_08000BAC(ExtendedRequestNode *, u32, u32, u16, u16, u16, u16);
extern u8 *func_080CBABC(u32 index);

/* Complete [0x08090A80, 0x08090BBC): 316 bytes, 114 instructions, including the literal pool. */
void func_08090A80(DisplayState *state)
{
    u32 i;

    state->first = func_08022840(0x1800);
    state->second = func_08022840(0xF00);
    data_0200F49C.value = 14;
    data_0200F498 = 8;
    data_0200F4A0.value = 0;
    data_0200F4A4.value = 8;
    for (i = 0; i < 14; ++i) {
        state->entries[i].data = data_083941E0[i].data;
        state->entries[i].tile = data_083941E0[i].tile + 0x1E0;
        state->entries[i].count = data_083941E0[i].count;
    }
    state->definitions = data_083941E0;
    func_08005318(data_083BF308, state->first, 1, 1);
    func_08005318(data_083C05E8, state->second, 1, 1);
    func_08000A98(&state->transfers[0], state->first, data_06013C00, 0xC00);
    func_08000A98(&state->transfers[1], state->second, data_06009C00, 0x780);
    func_08000BAC(&state->request, (u32)data_083C3864,
                   (u32)(data_030008B0.destination + 0x200), 30, 4, 60, 64);
    data_0836D4BC(data_03003B20, func_080CBABC(17), 32);
    data_0836D4BC(data_03003B20 - 0x200, func_080CBABC(16), 32);
    g_control_flags_03000940.display &= ~0x400;
}
