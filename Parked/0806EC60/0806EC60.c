#include "ffta.h"

// Complete [0x0806EC60, 0x0806ED30): 208 bytes, 104 instructions,
// including the literal word 0x08393B40 (data_08393B40).
typedef struct {
    u8 status;
    u8 entries[6];
    u8 count;
} DisplayState;

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

extern const u8 data_08393B40[6];
extern InventoryRecord *func_080CB210(u32 identifier, s32 *count);
extern u8 func_080CBD34(u16 identifier);

void func_0806EC60(DisplayState *state)
{
    u8 present[5];
    s32 count;
    InventoryRecord *records;
    u16 i;

    for (i = 0; i < 5; ++i)
        present[i] = 0;
    state->count = 0;

    records = func_080CB210(1, &count);
    for (i = 0; i < count; ++i) {
        if (records[i].quantity != 0)
            present[func_080CBD34(records[i].identifier)] = 1;
    }

    for (i = 0; i < 5; ++i) {
        if (present[i] == 1) {
            state->entries[state->count] = data_08393B40[i];
            state->count++;
        }
    }

    records = func_080CB210(0x16A, &count);
    for (i = 0; i < count; ++i) {
        u8 category = func_080CBD34(records[i].identifier);

        if (category == 5 && records[i].quantity != 0) {
            state->entries[state->count] = category;
            state->count++;
            break;
        }
    }
}
