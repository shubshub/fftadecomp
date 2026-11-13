#include "ffta.h"
#include "control_flags.h"

typedef struct E4CF4Descriptor {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    s16 kind;
    u16 flags;
    u32 unknown_18;
} E4CF4Descriptor;

typedef struct E4CF4Payload {
    u8 count;
    u8 current;
    u8 countdown;
    u8 flags;
    u8 selector;
    u8 unknown_05[3];
    void *effect;
    void *object;
    void *children[2];
    void *child;
} E4CF4Payload;

extern const u8 data_08396D34[];
extern const u8 data_0894D69C[];
extern const u8 data_088F46CC[];
extern u32 func_080E4B40(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *), u16 size,
                          const E4CF4Descriptor *descriptor, void *parent);
extern void func_080D38B4(void);
extern void *func_080D3E9C(const void *record, void *task);
extern void *func_080D3F08(void *effect);
extern void func_080D3F84(void *effect, u8 a, u8 b);
extern void func_080D7220(const void *record, u8 a, u8 b, s16 x, s16 y, u16 z);
extern u8 func_080D8858(void *object, u16 flags);
extern void *func_080DD4A4(void *object, u8 index);
extern void *func_080E03F8(void *object, const void *record, u8 count, u8 mode,
                          const s16 *position, void *parent);
extern u8 func_080E0570(void **children, u16 count);
extern void *func_080E05DC(void *child);
extern u16 func_080035A8(u8 layer);
extern u32 func_080035D0(u8 layer);

// Complete target: 0x080E4CF4..0x080E4EB0, 444 bytes.
u32 func_080E4CF4(void *task, E4CF4Descriptor *descriptor, E4CF4Payload *payload)
{
    E4CF4Descriptor request;
    u8 mode;
    u8 slot;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->flags;
        payload->object = descriptor->object;
        if (descriptor->kind == 0xB)
            payload->flags = 0;
        else
            payload->flags = 1;
        mode = 5;
        if (payload->selector != 0)
            mode = 0;
        payload->child = func_080E03F8(payload->object, data_08396D34, mode, 1, 0, task);
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
                payload->effect = func_080D3E9C(data_0894D69C, task);
                func_080D3F84(payload->effect, 12, 255);
                func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
                g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(3);
                g_control_flags_03000940.winout_hi = 0x3F;
                g_control_flags_03000940.display |= 0x8000;
                descriptor->phase++;
            } else {
                descriptor->phase = 2;
            }
        }
        break;
    case 0x101:
        payload->effect = func_080D3F08(payload->effect);
        func_080E0570(payload->children, 2);
        payload->countdown--;
        if (payload->countdown == 0) {
            slot = payload->children[0] != 0;
            request.kind = payload->current;
            request.flags = payload->flags;
            request.object = func_080DD4A4(payload->object, payload->current);
            payload->children[slot] = func_08005B6C(func_080E4B40, 0x2C, &request, task);
            payload->countdown = 0x40;
            payload->current++;
            if (payload->current == payload->count)
                descriptor->phase++;
        }
        break;
    case 0x102:
        payload->effect = func_080D3F08(payload->effect);
        if (payload->effect == 0) {
            if (func_080E0570(payload->children, 2)) {
                g_control_flags_03000940.display &= ~func_080035A8(3);
                g_control_flags_03000940.display &= 0x7FFF;
                descriptor->phase = 2;
            }
        }
        break;
    }
    return 0;
}
