// Target: complete [0x080EE13C, 0x080EE2F2), 438 bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *primary;
    u32 unknown_08[3];
    u16 index;
    u16 flag;
    u32 unknown_18;
} Descriptor;

typedef struct {
    u8 flag;
    u8 count;
    u8 index;
    u8 timer;
    void *primary;
    void *slots[2];
    void *stage;
    void *child;
} Payload;

extern const u8 data_0839957C[];
extern void func_080D38B4(void);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void *func_080E05DC(void *);
extern u8 func_080E0570(void **, u16);
extern u8 func_080D8858(void *, u32);
extern void *func_080EEEF0(u8, void *, void *);
extern void *func_080EEE50(void *, u8, void *);
extern void *func_080DD4A4(void *, u8);
extern u8 func_080DD494(void *);
extern u8 func_080EEF30(void *);
extern void *func_080EEF6C(void *);
extern u32 func_080EDFF8(void *, Descriptor *, void *);
extern void *func_08005B6C(u32 (*)(void *, Descriptor *, void *), u32, void *, void *);

u32 func_080EE13C(void *task, Descriptor *descriptor, Payload *payload)
{
    u8 mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->primary = descriptor->primary;
        mode = 5;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(payload->primary, data_0839957C, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (!payload->stage) {
            if (payload->flag) {
                payload->timer = 1;
                payload->count = func_080D8858(payload->primary, 0);
                descriptor->phase = 0x103;
            } else {
                payload->stage = func_080EEEF0(2, payload->primary, task);
                descriptor->phase++;
            }
        }
        break;
    case 0x101:
        payload->stage = func_080E05DC(payload->stage);
        if (!payload->stage) {
            payload->child = func_080EEE50(payload->primary, 2, task);
            if (func_080D8858(payload->primary, 0))
                payload->count = func_080D8858(payload->primary, 0);
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (!func_080DD494(payload->primary)) {
            payload->child = func_080EEF6C(payload->child);
            if (!payload->child)
                descriptor->phase = 2;
        } else if (payload->flag || func_080EEF30(payload->child)) {
            payload->timer = 1;
            descriptor->phase++;
        }
        break;
    case 0x103: {
        Descriptor local;
        u8 next;

        func_080E0570(payload->slots, 2);
        payload->timer--;
        if (payload->timer)
            break;
        next = payload->slots[0] != 0;
        local.primary = func_080DD4A4(payload->primary, payload->index);
        local.index = payload->index;
        payload->slots[next] = func_08005B6C(func_080EDFF8, 0x30, &local, task);
        payload->timer = 0x54;
        payload->index++;
        if (payload->index == payload->count)
            descriptor->phase++;
        break;
    }
    case 0x104:
        payload->child = func_080EEF6C(payload->child);
        if (!payload->child && func_080E0570(payload->slots, 2))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
