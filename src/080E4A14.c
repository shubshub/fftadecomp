#include "ffta.h"

typedef struct E4A14Descriptor {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 selector;
    u16 flags;
    u32 unknown_18;
} E4A14Descriptor;

typedef struct E4A14Payload {
    u8 selector;
    u8 flags;
    u8 count;
    u8 current;
    u8 countdown;
    u8 unknown_05[3];
    void *children[2];
    void *child;
    void *object;
} E4A14Payload;

extern const u8 g_object_08396CC0[];
extern const void *const g_object_08396CB8[];
extern u32 func_080E4844(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *), u16 size,
                          const E4A14Descriptor *descriptor, void *parent);
extern void func_080D38B4(void);
extern u8 func_080D8858(void *object, u16 flags);
extern void *func_080DD4A4(void *object, u8 index);
extern void *func_080E03F8(void *object, const void *record, u8 count, u8 mode,
                          const s16 *position, void *parent);
extern u8 func_080E0570(void **children, u16 count);
extern void *func_080E05DC(void *child);

/* Complete target: 0x080E4A14..0x080E4B3E, 298 bytes.
 * The request has the observed seven-word copied footprint. Only the reached
 * object/selector/flags fields are initialized here; other bytes remain unknown.
 * Helper and callback interfaces are conditional compatible ABI views.
 */
u32 func_080E4A14(void *task, E4A14Descriptor *descriptor, E4A14Payload *payload)
{
    E4A14Descriptor request;
    u8 slot;
    u8 count;

    switch (descriptor->phase) {
    case 0:
        payload->selector = (u8)descriptor->selector - 9;
        payload->flags = descriptor->flags;
        payload->object = descriptor->object;
        count = g_object_08396CC0[payload->selector];
        if (payload->flags != 0)
            count = 0;
        payload->child = func_080E03F8(payload->object,
            g_object_08396CB8[payload->selector], count, 1, 0, task);
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
            request.selector = payload->selector;
            request.flags = payload->current;
            request.object = func_080DD4A4(payload->object, payload->current);
            payload->children[slot] = func_08005B6C(func_080E4844, 0x2C,
                &request, task);
            payload->countdown = 0x38;
            payload->current++;
            if (payload->current == payload->count)
                descriptor->phase++;
        }
        break;
    case 0x102:
        if (func_080E0570(payload->children, 2))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
