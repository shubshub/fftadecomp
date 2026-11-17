#include "ffta.h"

// Target: complete [0x080F4C6C, 0x080F4DFC), 400 bytes, 200 instructions.
typedef struct {
    u16 phase;
    u16 unknown_02;
    s8 *placement;
    u8 unknown_08[12];
    u16 index;
} Descriptor080F4C6C;

typedef struct {
    u8 index;
    u8 unknown_01;
    u16 countdown;
    u8 first;
    u8 third;
    s16 x;
    s16 y;
    s16 width;
    u8 unknown_0c[4];
    void *objects[2];
} Payload080F4C6C;

extern const s8 data_08149D14[];
extern const s8 data_08149D18[];
extern const u8 data_08149D1C[];
extern const s8 data_08149D20[];
extern const u8 data_085000D8[];
extern void *func_080D5E80(const void *, u16, s16, s16, s16, s16, u8);
extern void func_08011118(void *, u8);
extern void func_08010884(void *, u8);
extern void func_08011058(void *, s16);
extern void *func_081443FC(void *, const void *, u32);
extern u8 func_080D5F24(void **, u16);

u32 func_080F4C6C(void *task, Descriptor080F4C6C *descriptor,
                  Payload080F4C6C *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            s8 *placement = descriptor->placement;

            payload->index = descriptor->index;
            payload->x = placement[0] * 32 + 16;
            payload->y = placement[1] * 16;
            payload->width = placement[2] * 32 + 16;
            payload->first = placement[0];
            payload->third = placement[2];
            payload->countdown = payload->index + 1;
        }
        break;
    case 1:
        break;
    case 0x100:
        {
            s8 a0[4], a1[4];
            s8 *a[2];
            u8 c[4];
            s8 b0[4], b1[4];
            s8 *b[2];
            u8 i;

            func_081443FC(a0, data_08149D14, 4);
            func_081443FC(a1, data_08149D18, 4);
            a[0] = a0;
            a[1] = a1;
            func_081443FC(c, data_08149D1C, 4);
            func_081443FC(b0, data_08149D20, 4);
            func_081443FC(b1, data_08149D14, 4);
            b[0] = b0;
            b[1] = b1;
            payload->countdown--;
            if (payload->countdown)
                break;
            for (i = 0; i < 2; i++) {
                if (a[i][payload->index] != -1) {
                    payload->objects[i] = func_080D5E80(
                        data_085000D8, a[i][payload->index],
                        payload->x, payload->y, payload->width, 0x392, 6);
                    func_08011118(payload->objects[i], c[payload->index]);
                    if (b[i][payload->index] == 0)
                        func_08010884(payload->objects[i], 1);
                    else
                        func_08011058(payload->objects[i], b[i][payload->index]);
                }
            }
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (func_080D5F24(payload->objects, 2))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
