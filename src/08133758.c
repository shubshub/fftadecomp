#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xD9];
    u8 field_103;
    u8 group;
} Unit133758;

typedef struct {
    u32 unknown_00;
    Unit133758 *unit;
    u8 unknown_08[0x1E];
    u16 flags;
} State133758;

typedef struct {
    u16 group : 4;
    u16 count : 7;
    u16 unknown_0B : 5;
    u8 unknown_02[2];
} __attribute__((packed)) GroupRecord;

typedef struct {
    u8 unknown_0000[0x3C3C];
    GroupRecord groups[24];
} Global133758;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern Global133758 g_state_02000000;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern u8 func_080C832C(Unit133758 *unit);
extern u8 func_080C95A8(u16 index);

/* Complete [0x08133758, 0x081337F2): 154 bytes, 64 instructions.
 * f0b5041ce18c10200840002842d1606894f7e0fd000600283cd06268118d1648
 * 084010850022154e15483518930029780907606882277f00c019090f00788142
 * 24d110490e4ab01818180a6804210ef051fd60680c4d4019007800281ad00d20
 * 95f7f6fe0006000e012813d0616849190878013808700de0bfff000000000002
 * 3c3c0000b8d436080301000004350132172acbddf0bc01bc0047
 */
void func_08133758(State133758 *state)
{
    s32 i;

    if (!(state->flags & 0x10) && func_080C832C(state->unit)) {
        state->unit->flags &= ~0x40;
        for (i = 0; i < 24; i++) {
            if (g_state_02000000.groups[i].group == state->unit->group) {
                g_callbacks_0836D4B8[0](&g_state_02000000.groups[i], sizeof(GroupRecord));
                if (state->unit->field_103 != 0 && func_080C95A8(13) != 1)
                    state->unit->field_103--;
                return;
            }
        }
    }
}
