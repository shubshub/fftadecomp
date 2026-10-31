/* Complete target [0x08127458, 0x08127592): 314 bytes.
 * f0 b5 57 46 4e 46 45 46 e0 b4 82 b0 06 1c b1 7b cc 09 7f 20 08 40 b0 73
 * 71 68 08 22 88 5e 80 46 08 23 f0 5e 0c 23 ca 5e 91 46 0a 22 b1 5e 43 46
 * 1b 18 9a 46 4a 46 52 18 01 92 03 1c 43 43 18 1c 0a 1c 4a 43 11 1c 40 18
 * 1a f0 fa f9 00 04 02 0c 00 2c 0e d0 b4 89 10 1c 21 1c 1b f0 01 f9 00 04
 * 07 0c 20 1c 00 21 03 0c 0a 04 19 1c 11 43 00 04 15 e0 b7 89 10 1c 00 21
 * 03 0c 0a 04 19 1c 11 43 00 04 03 0c 0a 04 19 1c 11 43 00 04 3a 1c 00 23
 * 15 0c 1c 04 2b 1c 23 43 12 04 1a f0 c5 fe b0 64 f1 64 30 1c 18 30 41 46
 * 52 46 13 04 1b 14 3c 04 24 14 00 94 00 22 e0 f6 87 f8 30 1c 30 30 49 46
 * 01 9a 13 04 1b 14 00 94 00 22 e0 f6 7d f8 1c 23 f0 5e 18 22 b1 5e 40 1a
 * 01 21 00 28 02 da 01 23 5b 42 19 1c 31 74 34 21 70 5e 30 22 b1 5e 40 1a
 * 01 21 00 28 02 da 01 23 5b 42 19 1c 71 74 70 68 0e 22 b2 56 01 21 00 23
 * 70 f7 04 ff 70 68 00 21 02 22 73 f7 01 f8 70 68 72 f7 e4 ff 01 1c f1 73
 * 08 06 00 28 01 d0 48 1e f0 73 02 b0 38 bc 98 46 a1 46 aa 46 f0 bc 01 bc
 * 00 47
 */
#include "ffta.h"

typedef signed long long s64;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    u16 unknown_0A;
    s16 y;
} Object08127458;

typedef struct {
    u16 first;
    u16 second;
    u16 target_first;
    u16 target_second;
    u16 step_first;
    u16 step_second;
    s16 delta_first;
    s16 delta_second;
    s16 error;
    s16 half_second;
    s16 remaining;
    u16 unknown_16;
} Transition08127458;

typedef struct {
    void *output;
    Object08127458 *object;
    s16 x;
    s16 y;
    u16 amount;
    u8 flags;
    u8 counter;
    s8 direction_x;
    s8 direction_y;
    u8 unknown_12[6];
    Transition08127458 first;
    Transition08127458 second;
    s64 step;
} Payload08127458;

extern u32 func_08141898(u32 value);
extern s32 func_081426B8(s32 first, s32 second);
extern s64 func_08142280(s64 first, s64 second);
extern void func_08007620(void *state, u16 first, u16 second,
                          u16 target_first, u16 target_second);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern u32 func_0809A53C(Object08127458 *object);

void func_08127458(Payload08127458 *payload)
{
    u32 mode;
    s32 start_x;
    s32 start_y;
    s32 delta_x;
    s32 delta_y;
    s32 target_x;
    s32 target_y;
    u16 scalar;
    u16 amount;
    u32 count;

    mode = payload->flags >> 7;
    payload->flags &= 0x7F;
    start_x = payload->object->x;
    delta_x = payload->x;
    start_y = payload->object->y;
    delta_y = payload->y;
    target_x = start_x + delta_x;
    target_y = start_y + delta_y;
    scalar = func_08141898((u32)(delta_x * delta_x) +
                           (u32)(delta_y * delta_y));
    if (mode) {
        amount = func_081426B8(scalar, payload->amount);
        payload->step = (s64)payload->amount << 16;
    } else {
        amount = payload->amount;
        payload->step = func_08142280((s64)scalar << 32,
                                      (s64)amount << 16);
    }
    func_08007620(&payload->first, start_x, 0, target_x, amount);
    func_08007620(&payload->second, start_y, 0, target_y, amount);
    payload->direction_x = (s16)payload->first.target_first -
                           (s16)payload->first.first >= 0 ? 1 : -1;
    payload->direction_y = (s16)payload->second.target_first -
                           (s16)payload->second.first >= 0 ? 1 : -1;
    func_0809836C(payload->object, 1, (s8)payload->flags, 0);
    func_0809A570(payload->object, 0, 2);
    count = func_0809A53C(payload->object);
    payload->counter = count;
    if (payload->counter != 0)
        payload->counter = count - 1;
}
