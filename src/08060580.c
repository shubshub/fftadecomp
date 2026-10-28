#include "ffta.h"

typedef struct {
    u8 type;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x1B];
    u8 second_count;
    u8 unknown_1C[4];
    MenuRecord *records[1];
} MenuState;

extern MenuState *data_0200F44C;
extern const u16 data_0852A13E[];
extern u16 func_080CB53C(u8 type);

/* Complete target: [0x08060580, 0x08060618), 152 bytes, 65 instructions. */
u16 func_08060580(const u8 *mode, s16 selection)
{
    u16 result = 0;

    switch (*mode)
    {
    case 1:
        result = data_0852A13E[selection + 0x29] + 1;
        break;
    case 5:
        if (selection <= 1)
        {
            MenuState *state = data_0200F44C;
            s32 index = selection - 2;
            MenuRecord *record;

            index += state->second_count;
            record = state->records[index];
            if (!record || !record->type)
                result = data_0852A13E[0x40] + 1;
            else
                result = func_080CB53C(record->type) + 1;
        }
        else
            result = data_0852A13E[0x43] + 1;
        break;
    case 6:
        result = func_080CB53C(data_0200F44C->records[selection]->type) + 1;
        break;
    }
    return result;
}
