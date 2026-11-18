#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[6];
    u16 message;
    u8 mode;
    u8 timer;
    u8 unknown_52[2];
    u32 flags;
    s32 saved_result;
    s32 result;
    u32 unknown_60;
    u16 field_64;
    u16 field_66;
} CommandState;

typedef struct {
    u8 unknown_00[0x1F64];
    u32 resource;
} GlobalState;

extern CommandState *data_0200F450;
extern u8 g_state_02000000[];
extern u32 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08013364(void);

static inline void queue_command(CommandState *state, u16 command)
{
    state->current = command;
    state->entries[state->count++] = state->current;
}

/* State dispatcher table 0x08393918, slot 25. */
void func_080633F8(void)
{
    s8 choice;

    if ((u16)func_08011860() == 0)
        return;
    choice = func_08013380();
    if (choice < 0) {
        data_0200F450->flags &= ~1u;
        func_08013364();
        queue_command(data_0200F450, 0x17);
        queue_command(data_0200F450, 0x34);
        data_0200F450->current = 0x42;
    } else if (choice > 0) {
        data_0200F450->flags &= ~1u;
        data_0200F450->message = 0xBB;
        queue_command(data_0200F450, 0x1C);
        queue_command(data_0200F450, 0x34);
        queue_command(data_0200F450, 0x35);
        data_0200F450->current = 0x42;
    } else if (((GlobalState *)g_state_02000000)->resource < 5000) {
        data_0200F450->flags &= ~1u;
        data_0200F450->message = 0xCC;
        queue_command(data_0200F450, 0x1C);
        queue_command(data_0200F450, 0x34);
        queue_command(data_0200F450, 0x35);
        data_0200F450->current = 0x42;
    } else {
        data_0200F450->result = data_0200F450->saved_result =
            ((const Record *)(g_state_02000000 + 0x20D0))->field_04;
        data_0200F450->timer = 0x10;
        data_0200F450->field_64 = 0x9001;
        data_0200F450->field_66 = 0x1234;
        data_0200F450->message = 0xBA;
        queue_command(data_0200F450, 0x1A);
        queue_command(data_0200F450, 0x15);
        queue_command(data_0200F450, 0x37);
        queue_command(data_0200F450, 0x2B);
        queue_command(data_0200F450, 0x28);
        queue_command(data_0200F450, 0x39);
        queue_command(data_0200F450, 0x3B);
        queue_command(data_0200F450, 0x34);
        queue_command(data_0200F450, 0x35);
        data_0200F450->current = 0x43;
    }
}
