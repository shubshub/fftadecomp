#include "ffta.h"

// Complete target [0x08118C4C, 0x08118D20): 212 bytes.

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
} Descriptor08118C4C;

typedef struct {
    u16 timer;
    u8 unknown_02[2];
    void *finish_child;
    void *object;
    void *script_child;
} Payload08118C4C;

extern u8 data_03003920[];
extern const u8 data_083A6208[];

extern void func_0814186C(const void *, void *, u32);
extern void *func_080E03F8(void *, const void *, u8, u8, const u32 *, void *);
extern void *func_080E05DC(void *);
extern void *func_080E5694(void *);
extern void *func_080E051C(void *);
extern void func_080DBED4(u32, u32, u32, u32);

u32 func_08118C4C(void *task, Descriptor08118C4C *descriptor,
                  Payload08118C4C *payload)
{
    switch (descriptor->phase) {
    case 0:
    {
        u16 fill;
        u16 fill2;
        u32 position;

        payload->object = descriptor->object;
        position = 0x00F80078;
        fill = 0;
        func_0814186C(&fill, data_03003920, 0x01000040);
        fill2 = 0;
        func_0814186C(&fill2, data_03003920 + 0x200, 0x01000070);
        payload->script_child = func_080E03F8(payload->object, data_083A6208,
                                              4, 6, &position, task);
        break;
    }
    case 1:
        break;
    case 0x100:
        payload->script_child = func_080E05DC(payload->script_child);
        if (payload->script_child == 0) {
            payload->finish_child = func_080E5694(task);
            payload->timer = 0x41;
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (payload->timer != 0) {
            payload->timer--;
            if (payload->timer == 0)
                func_080DBED4(0, 1, 0, 0);
        }
        payload->finish_child = func_080E051C(payload->finish_child);
        if (payload->finish_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
