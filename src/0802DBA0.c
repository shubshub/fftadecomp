#include "ffta.h"

// Complete target: [0x0802DBA0, 0x0802DC60), 192 bytes, 76 instructions.

typedef struct {
    u8 unknown_00[0x104];
    u8 identifier;
    u8 unknown_105[3];
} Unit;

// One object: the ROM reaches second_units as units + 0x2F44 and setup_value
// as second_units - 0x1059, so the three are fields of a single block.
typedef struct {
    u8 unknown_00[0x80];
    Unit units[24];
    u8 unknown_1940[0x1F6B - 0x1940];
    u8 setup_value;
    u8 unknown_1F6C[0x2FC4 - 0x1F6C];
    Unit second_units[12];
    u8 unknown_3C24[0x3C3C - 0x3C24];
    u8 buffer[0x60];
} GlobalState;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern GlobalState g_state_02000000;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern u8 func_080C95A8(u16 selector);
extern void *func_08096D7C(void);
extern void *func_0809A9C0(u8 *context, s32 index);
extern void func_0802D824(void);
extern void func_0802DA00(u8 value);
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer callback);
extern void func_080C95C0(u16 index, u32 value);

void func_0802DBA0(void)
{
    Unit *unit;
    BufferInitializer const *callbacks;
    s32 i;

    if ((u8)func_080C95A8(13) == 1) {
        for (i = 0; i < 2; i++) {
            unit = func_0809A9C0(func_08096D7C(), i);
            unit->identifier = 0xFF;
        }
    }

    // Unlike the loop above, these two loops read the byte back before
    // storing it (ldrb/orrs/strb).
    unit = g_state_02000000.units;
    for (i = 0; i < 24; i++, unit++)
        unit->identifier |= 0xFF;
    unit = g_state_02000000.second_units;
    for (i = 0; i < 12; i++, unit++)
        unit->identifier |= 0xFF;

    func_0802D824();
    if ((u8)func_080C95A8(13) != 1)
        func_0802DA00(g_state_02000000.setup_value);
    callbacks = g_callbacks_0836D4B8;
    func_0814224C(g_state_02000000.buffer, 0x60, callbacks[0]);
    func_080C95C0(12, 0);
}
