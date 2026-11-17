#include "ffta.h"

typedef struct Descriptor {
    u16 phase;
    u16 unknown_02;
    void *primary;
    u32 unknown_08[3];
    u16 unknown_14;
    u16 flag;
    u32 unknown_18;
} Descriptor;

typedef struct Payload {
    u8 flag;
    u8 unknown_01;
    u16 countdown;
    void *entity;
    void *primary;
    void *stage;
    u32 unknown_10;
    void *effect;
    void *task18;
    void *task1c;
} Payload;

extern const u8 data_0839BAA8[];
extern const u8 data_0839BAF0[];
extern const u8 data_0839BB08[];
extern void func_080D38B4(void);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DD47C(void *);
extern void func_080DE10C(void *, int);
extern void func_080DE3BC(void *, int);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D8858(void *, u16);
extern u32 func_080E4054(void *, void *, void *);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *), u16 size, void *descriptor, void *parent);
extern void *func_080D6134(void *);
extern void *func_080E051C(void *);

// Target: complete [0x080F7160, 0x080F72AE), 334 bytes.
u32 func_080F7160(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 mode;
        payload->flag = descriptor->flag;
        payload->primary = descriptor->primary;
        mode = 6;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(payload->primary, data_0839BAA8, mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        s16 x, y;
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage)
            break;
        if (func_080D3B54(payload->primary)) {
            descriptor->phase = 2;
            break;
        }
        payload->entity = func_080DD47C(payload->primary);
        func_080DE10C(payload->entity, 0x24);
        func_080DE3BC(payload->entity, 1);
        func_080DBDC8(payload->entity, &x, &y);
        payload->effect = func_080D6098(x, y, 0, 1, 1, &payload->unknown_10, data_0839BAF0, task);
        payload->task1c = func_080DFD8C(data_0839BB08, 1, 4, 0, task);
        payload->countdown = 0x14;
        descriptor->phase++;
        break;
    }
    case 0x101:
        payload->countdown--;
        if (payload->countdown)
            break;
        if (func_080D8858(payload->primary, 0)) {
            Descriptor child;
            child.unknown_14 = 0x65;
            child.flag = 1;
            child.primary = payload->primary;
            payload->task18 = func_08005B6C(func_080E4054, 0x1c, &child, task);
            descriptor->phase++;
        } else
            descriptor->phase = 2;
        break;
    case 0x102:
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->task18 = func_080E051C(payload->task18);
        if (payload->task18)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
