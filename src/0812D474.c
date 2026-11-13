#include "ffta.h"

// Target: complete [0x0812D474, 0x0812D5A0), 300 bytes, including the
// 32-entry jump table and the value-list literals.
typedef struct {
    u8 unknown_0000[0x1F64];
    u32 unknown_1F64;
} GameState;

extern s32 func_080C7EA4(const void *object, u32 selector);
extern u32 func_0812D424(const void *object, const u16 *values, s32 count);
extern u8 func_08132EA0(void *actor, void *object);
extern u8 func_08133BC4(void *object);

extern const u16 data_083A8472[];
extern const u16 data_083A8478[];
extern const u16 data_083A847C[];
extern const u16 data_083A8482[];
extern const u16 data_083A844C[];
extern GameState g_state_02000000;

u8 func_0812D474(void *actor, void *object, u32 condition)
{
    const u16 *values;
    s32 count;

    switch (condition) {
    case 15:
        count = 3;
        values = data_083A8472;
        break;
    case 27:
        count = 1;
        values = data_083A8482;
        break;
    case 16:
        count = 3;
        values = data_083A847C;
        break;
    case 37:
        count = 19;
        values = data_083A844C;
        break;
    case 7:
        count = 2;
        values = data_083A8478;
        break;
    case 9:
        if (func_08133BC4(object) && !g_state_02000000.unknown_1F64)
            return 0;
        return 1;
    case 17:
        if (func_080C7EA4(object, 7))
            return 1;
        return 0;
    case 6:
        if (func_080C7EA4(object, 0x26))
            return 1;
        return 0;
    case 8:
        return func_08132EA0(actor, object);
    default:
        return 0;
    }
    return func_0812D424(object, values, count);
}
