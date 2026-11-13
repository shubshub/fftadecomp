// Target: complete [0x080E6590, 0x080E6714), 388 bytes.
#include "control_flags.h"

typedef struct E6590Descriptor {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 index;
    u16 selector;
    u32 unknown_18;
} E6590Descriptor;

typedef struct E6590Payload {
    u8 count;
    u8 current;
    u8 countdown;
    u8 selector;
    void *object;
    void *children[2];
    void *child;
} E6590Payload;

extern const u8 g_object_0839735C[];
extern u32 func_080E61E4(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *), u16 size,
                          const E6590Descriptor *descriptor, void *parent);
extern void func_080D38B4(void);
extern u8 func_080D8858(void *object, u16 flags);
extern void *func_080DD4A4(void *object, u8 index);
extern void *func_080E03F8(void *object, const void *record, u8 count, u8 mode,
                          const s16 *position, void *parent);
extern u8 func_080E0570(void **children, u16 count);
extern void *func_080E05DC(void *child);
extern u16 func_080035A8(u8 index);
extern u16 func_080035D0(u8 index);

u32 func_080E6590(void *task, E6590Descriptor *descriptor, E6590Payload *payload)
{
    E6590Descriptor request;
    u8 slot;
    u8 count;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->object = descriptor->object;
        count = 6;
        if (payload->selector != 0)
            count = 0;
        payload->child = func_080E03F8(payload->object, g_object_0839735C,
            count, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->child = func_080E05DC(payload->child);
        if (payload->child == 0) {
            payload->count = func_080D8858(payload->object, 0);
            if (payload->count != 0) {
                payload->countdown = 1;
                g_control_flags_03000940.winin_lo = 0x3F & ~func_080035D0(3);
                g_control_flags_03000940.winin_hi =
                    0x3F & ~(func_080035D0(2) | func_080035D0(3));
                g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
                descriptor->phase++;
            } else {
                descriptor->phase = 2;
            }
        }
        break;
    case 0x101:
        func_080E0570(payload->children, 2);
        payload->countdown--;
        if (payload->countdown == 0) {
            slot = payload->children[0] != 0;
            request.object = func_080DD4A4(payload->object, payload->current);
            request.index = payload->current;
            payload->children[slot] = func_08005B6C(func_080E61E4, 0x40,
                &request, task);
            payload->countdown = 0x44;
            payload->current++;
            if (payload->current == payload->count)
                descriptor->phase++;
        }
        break;
    case 0x102:
        if (func_080E0570(payload->children, 2)) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            g_control_flags_03000940.display &= ~func_080035A8(3);
            g_control_flags_03000940.display &= 0x9FFF;
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
