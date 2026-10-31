#include "ffta.h"

typedef void (*Initializer080A8194)(void *object, u32 size);

extern Initializer080A8194 g_callbacks_0836D4B8[];
extern void *func_08022840(u32 size);
extern void func_08022854(u8 *object);
extern void func_080A433C(void *object, void *context, s32 first, s32 second,
                          u32 value_a, u32 value_b, u32 flag, u32 variant);

/* Complete [0x080A8194, 0x080A8264): 208 bytes, 90 instructions.
 * Target: f0b557464e464546e0b488b004901098129c0904090c05911204120c06921b061b0e99460006000e82462406240e0794234c201c7af73afb061c22480268301c211c9af039f8b12080008046351c1c35341c1d4977181b480268201c41469af02bf8ff202870b12080002d182418bc42f1dd49460a061216504603061b16059900910698019011980006000e029007990391301c0499fcf787f80c4970180078002803d1301c7af70bfb0026301c08b038bc9846a146aa46f0bc02bc0847000098340000b8d43608f4230000bd260000
 */
void *func_080A8194(void *context, u16 value_a, u16 value_b,
                    u8 first, u8 second, u8 flag, u8 variant)
{
    u8 *object;
    u8 *cursor;
    u8 *marker;
    s32 last;

    object = func_08022840(0x3498);
    g_callbacks_0836D4B8[0](object, 0x3498);
    marker = object + 0x1C;
    cursor = object;
    last = (s32)(object + 0x23F4);
    do {
        g_callbacks_0836D4B8[0](cursor, 0x2C4);
        *marker = 0xFF;
        marker += 0x2C4;
        cursor += 0x2C4;
    } while ((s32)cursor <= last);

    func_080A433C(object, context, (s8)first, (s8)second,
                  value_a, value_b, flag, variant);
    if (object[0x26BD] == 0) {
        func_08022854(object);
        object = 0;
    }
    return object;
}
