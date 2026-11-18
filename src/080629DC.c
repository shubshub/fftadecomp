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
    u8 unknown_68[0x820];
    u32 selection;
} CommandState;

typedef struct {
    u8 unknown_00[0x20D0];
    u32 selection;
    u8 unknown_20D4[0xCA];
    u16 key;
} GlobalState;

typedef struct {
    u16 key : 10;
    u16 unknown : 6;
} __attribute__((packed)) SelectionRecord;

extern CommandState *data_0200F450;
extern GlobalState g_state_02000000;
extern u32 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08013364(void);
extern u32 func_08066114(void);

static inline void queue_command(CommandState *state, u16 command)
{
    state->current = command;
    state->entries[state->count++] = state->current;
}

/* State dispatcher table 0x08393918, slot 11. */
void func_080629DC(void)
{
    s8 choice;

    if ((u16)func_08011860() == 0)
        return;
    choice = func_08013380();
    if (choice < 0) {
        func_08013364();
        queue_command(data_0200F450, 0x8);
        data_0200F450->current = 0x34;
    } else if (choice > 0) {
        data_0200F450->flags |= 2;
        data_0200F450->result = -1;
        data_0200F450->message = 0xAD;
        data_0200F450->mode = 3;
        data_0200F450->field_64 = 0x9001;
        data_0200F450->field_66 = 0x1234;
        func_08013364();
        queue_command(data_0200F450, 0x30);
        queue_command(data_0200F450, 0x39);
        queue_command(data_0200F450, 0x3B);
        queue_command(data_0200F450, 0x34);
        queue_command(data_0200F450, 0x33);
        queue_command(data_0200F450, 0x29);
        queue_command(data_0200F450, 0x28);
        queue_command(data_0200F450, 0x39);
        data_0200F450->current = 0x34;
    } else {
        const SelectionRecord *record;

        data_0200F450->flags |= 2;
        record = (const SelectionRecord *)func_08066114();
        data_0200F450->result = record->key;
        data_0200F450->message = 0xC6;
        data_0200F450->mode = 8;
        data_0200F450->field_64 = 0x9001;
        data_0200F450->field_66 = 0x1234;
        g_state_02000000.key = data_0200F450->result;
        g_state_02000000.selection = data_0200F450->selection;
        queue_command(data_0200F450, 0xC);
        queue_command(data_0200F450, 0x2A);
        queue_command(data_0200F450, 0x28);
        queue_command(data_0200F450, 0x39);
        queue_command(data_0200F450, 0x38);
        queue_command(data_0200F450, 0x29);
        queue_command(data_0200F450, 0x28);
        queue_command(data_0200F450, 0x39);
        queue_command(data_0200F450, 0x34);
        data_0200F450->current = 0x35;
    }
}
