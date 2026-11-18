#include "ffta.h"

// Target: complete [0x08118A08, 0x08118AC0), 184 bytes, 75 reachable instructions.
// Local offset views; original declarations and full extents are unknown.
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
} Descriptor08118A08;

typedef struct {
    u32 unknown_00;
    void *scripted_child;
    void *actor;
    void *initial_child;
} Payload08118A08;

extern const u8 data_083A6110[];
extern u16 data_03003920[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void *func_080E05DC(void *);
extern void *func_080F2E40(u8, void *, void *);
extern void *func_080F1210(void *);

u32 func_08118A08(void *task, Descriptor08118A08 *descriptor,
                  Payload08118A08 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u16 first;
            u16 second;
            u32 parameter;

            payload->actor = descriptor->actor;
            parameter = 0x00B80068;
            first = 0;
            func_0814186C(&first, data_03003920, 0x01000040);
            second = 0;
            func_0814186C(&second, data_03003920 + 0x100, 0x01000070);
            payload->initial_child = func_080E03F8(payload->actor,
                data_083A6110, 3, 6, &parameter, task);
        }
        break;
    case 1:
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        payload->scripted_child = func_080F2E40(1, payload->actor, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->scripted_child = func_080F1210(payload->scripted_child);
        if (payload->scripted_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
