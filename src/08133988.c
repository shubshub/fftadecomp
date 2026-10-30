#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 kind;
} ActionRecord;

typedef struct {
    u8 unknown_00[0x30];
    ActionRecord *record;
} ActionState;

typedef struct {
    u32 value;
    u32 unknown_04;
    s8 mode;
    u8 unknown_09[3];
} ActionDescriptor;

extern ActionState data_0200F3F0;
extern const ActionDescriptor data_083A87B0[];

/* 08133988..081339A8: 32 bytes, including the state and descriptor-table literals. */
s32 func_08133988(void)
{
    ActionState *state = &data_0200F3F0;

    return data_083A87B0[state->record->kind].mode;
}
