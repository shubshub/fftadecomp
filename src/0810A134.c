// Target: complete [0x0810A134, 0x0810A2A4), 368 bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
} Descriptor0810A134;

typedef struct {
    u8 unknown_00[4];
    u16 frame;
    u8 count;
    u8 delay;
    void *objects[15];
    void *fade_task;
    void *label_task;
} Payload0810A134;

typedef struct {
    u8 frame;
    u8 id;
    s16 y;
} Entry0810A134;

extern const u8 data_088F669C[];
extern const u8 data_0894DDDC[];
extern const u8 data_083A1B30[];
extern const Entry0810A134 data_083A1B38[];
extern const u8 data_085080A8[];

extern void func_080D7220(const void *, u32, u32, u32, u32, u32);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D5CC0(const void *, u8, s16, s16, s16, u8, u8, u8);
extern void func_080107D4(void *, s16, s16, s16);
extern u8 func_080D5F24(void **, u16);
extern void *func_080D3F08(void *);

u32 func_0810A134(void *task, Descriptor0810A134 *descriptor,
                  Payload0810A134 *payload)
{
    u8 i;
    u16 a;
    u16 b;
    u16 c;

    switch (descriptor->phase) {
    case 1:
        break;
    case 0x100:
        func_080D7220(data_088F669C, 0, 2, 0x78, 0, 0);
        payload->fade_task = func_080D3E9C(data_0894DDDC, task);
        payload->label_task = func_080DFD8C(data_083A1B30, 1, 4, 0, task);
        payload->delay = 3;
        descriptor->phase++;
        break;
    case 0x101:
        for (i = payload->count; i <= 14; i++) {
            if (payload->frame == data_083A1B38[i].frame) {
                payload->objects[i] = func_080D5CC0(data_085080A8,
                    data_083A1B38[i].id, data_083A1B38[i].y, 8, 0x3FC, 6, 1, 0);
                payload->count++;
            }
        }
        payload->delay--;
        if (payload->delay != 0) {
            for (i = 0; i <= 14; i++) {
                if (payload->objects[i] != 0) {
                    func_08011040((Struct08011040 *)payload->objects[i], &a, &b, &c);
                    b++;
                    func_080107D4(payload->objects[i], a, b, c);
                }
            }
        } else {
            payload->delay = 3;
        }
        payload->frame++;
        if (func_080D5F24(payload->objects, 15) && payload->count > 14)
            descriptor->phase++;
        break;
    case 0x102:
        payload->fade_task = func_080D3F08(payload->fade_task);
        if (payload->fade_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
