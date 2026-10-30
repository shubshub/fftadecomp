#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[6];
    u16 field_4E;
    u8 mode;
    u8 unknown_51[3];
    u32 flags;
    s32 saved_result;
    u8 unknown_5C[8];
    u16 field_64;
    u16 field_66;
    u8 unknown_68[0x81];
    u8 field_E9;
} CommandState0806261C;

typedef struct {
    u8 flags;
} Mode0806261C;

extern CommandState0806261C *data_0200F450;
extern Mode0806261C data_030028A0;
extern void func_08064E7C(void);
extern void func_08066120(u8 index);

/* Target [0x0806261C, 0x080627EC), 464 complete bytes:
 * 70b51d4d2a68506d412149420840506502f026fc194801780826301c08400028
 * 2ed02c68a16d022900d17de0022930dc012900d0c9e0201ce93000780140a922
 * 002900d0a822201c4e300280211c5031072008702a6816805088411c51800004
 * c00b131d18180680382414805088411c51800004c00b74e050f40002a0280003
 * 2c68a16d02294fd0022902dc012903d09be0032973d098e0201ce93000780140
 * ab22002900d0aa22201c4e300280211c64311b48088002311a480880201c5030
 * 06702a680e2414805088411c51800004c00b131d181804802a2414805088411c
 * 51800004c00b18180480282414805088411c51800004c00b1818048039241480
 * 5088411c51800004c00b18180480382414805088411c51800004c00b21e00000
 * 0190000034120000201ce930017801200840b721002800d0b621201c4e300180
 * 606d0521494208406065042003f0dafc2a68132414805088411c51800004c00b
 * 131d18180480342414805088411c51800004c00b1b181c803520108025e0201c
 * e930017801200840bf21002800d0be21201c4e300180606d0521494208406065
 * 1f2323806088411c61800004c00b221d10180380342323806088411c61800004
 * c00b121813803520208070bc01bc0047
 */
void func_0806261C(void)
{
    data_0200F450->flags &= ~0x40u;
    func_08064E7C();
    if (data_030028A0.flags & 8) {
        switch (data_0200F450->saved_result) {
        case 1: {
            CommandState0806261C *head = data_0200F450;
            CommandState0806261C *state;

            head->field_4E = (head->field_E9 & 1) ? 0xA8 : 0xA9;
            head->mode = 7;
            state = data_0200F450;
            state->current = 0x08;
            state->entries[state->count++] = state->current;
            state->current = 0x38;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x35;
            break;
        }
        case 2: {
            CommandState0806261C *head = data_0200F450;
            CommandState0806261C *state;

            head->field_4E = (head->field_E9 & 1) ? 0xB6 : 0xB7;
            head->flags &= ~4u;
            func_08066120(4);
            state = data_0200F450;
            state->current = 0x13;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x35;
            break;
        }
        case 3: {
            CommandState0806261C *state = data_0200F450;

            state->field_4E = (state->field_E9 & 1) ? 0xBE : 0xBF;
            state->flags &= ~4u;
            state->current = 0x1F;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x35;
            break;
        }
        }
    } else {
        switch (data_0200F450->saved_result) {
        case 1: {
            CommandState0806261C *head = data_0200F450;
            CommandState0806261C *state;

            head->field_4E = (head->field_E9 & 1) ? 0xAA : 0xAB;
            head->field_64 = 0x9001;
            head->field_66 = 0x1234;
            head->mode = 8;
            state = data_0200F450;
            state->current = 0x0E;
            state->entries[state->count++] = state->current;
            state->current = 0x2A;
            state->entries[state->count++] = state->current;
            state->current = 0x28;
            state->entries[state->count++] = state->current;
            state->current = 0x39;
            state->entries[state->count++] = state->current;
            state->current = 0x38;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x35;
            break;
        }
        case 2: {
            CommandState0806261C *head = data_0200F450;
            CommandState0806261C *state;

            head->field_4E = (head->field_E9 & 1) ? 0xB6 : 0xB7;
            head->flags &= ~4u;
            func_08066120(4);
            state = data_0200F450;
            state->current = 0x13;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x35;
            break;
        }
        case 3: {
            CommandState0806261C *state = data_0200F450;

            state->field_4E = (state->field_E9 & 1) ? 0xBE : 0xBF;
            state->flags &= ~4u;
            state->current = 0x1F;
            state->entries[state->count++] = state->current;
            state->current = 0x34;
            state->entries[state->count++] = state->current;
            state->current = 0x35;
            break;
        }
        }
    }
}
