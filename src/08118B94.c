#include "ffta.h"

// Complete target [0x08118B94, 0x08118C4C): 184 bytes.

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
} Descriptor08118B94;

typedef struct {
    u8 unknown_00[4];
    void *finish_child;
    void *object;
    void *script_child;
} Payload08118B94;

extern u8 data_03003920[];
extern const u8 data_083A61C0[];

extern void func_0814186C(const void *, void *, u32);
extern void *func_080E03F8(void *, const void *, u8, u8, const u32 *, void *);
extern void *func_080E05DC(void *);
extern void *func_080F2E40(u8, void *, void *);
extern void *func_080F1210(void *);

u32 func_08118B94(void *task, Descriptor08118B94 *descriptor,
                  Payload08118B94 *payload)
{
    switch (descriptor->phase) {
    case 0:
    {
        u16 fill;
        u16 fill2;
        u32 position;

        payload->object = descriptor->object;
        position = 0x01180038;
        fill = 0;
        func_0814186C(&fill, data_03003920, 0x01000040);
        fill2 = 0;
        func_0814186C(&fill2, data_03003920 + 0x200, 0x01000070);
        payload->script_child = func_080E03F8(payload->object, data_083A61C0,
                                              2, 6, &position, task);
        break;
    }
    case 1:
        break;
    case 0x100:
        payload->script_child = func_080E05DC(payload->script_child);
        if (payload->script_child == 0) {
            payload->finish_child = func_080F2E40(2, payload->object, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->finish_child = func_080F1210(payload->finish_child);
        if (payload->finish_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
