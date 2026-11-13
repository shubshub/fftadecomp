#include "ffta.h"

// Target: 0x0810E8FC..0x0810EA76, 378 bytes, 189 instructions.
typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    s16 kind;
    u16 mode;
} Event;

typedef struct {
    u8 count;
    u8 index;
    s8 delay;
    u8 unknown_03;
    u8 kind;
    u8 mode;
    u8 unknown_06[6];
    void *children[4];
    void *unknown_1c;
    void *unknown_20;
    void *transition;
    void *object;
} State;

typedef struct {
    u32 unknown_00;
    void *unknown_04;
    u8 unknown_08[12];
    u16 index;
    u16 kind;
    u32 unknown_18;
} Child;

typedef u32 (*TaskCallback)(void *task, void *request, void *payload);

extern u8 data_083A2C54[];
extern void *func_080E03F8(void *object, const void *descriptor, u32 mode,
                           u32 priority, u32 flags, void *parent);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *transition);
extern u8 func_080DD494(void *object);
extern void *func_080DD47C(void *object);
extern void *func_080DD214(void *object, u32 unknown_1, u32 unknown_2,
                           void *parent);
extern u8 func_080D8858(void *object, u32 index);
extern void *func_080DD4A4(void *object, u32 index);
extern void func_080DD4C4(void);
extern void func_080DB838(void);
extern u8 func_080D8B4C(void);
extern u8 func_080E0570(void **children, u32 count);
extern void *func_080DBA5C(void *attachment);
extern u32 func_0810E738(void *task, void *request, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);

u32 func_0810E8FC(void *task, Event *event, State *s)
{
    Child child;
    u32 animation;
    u32 slot;

    switch (event->state) {
    case 0:
        s->mode = event->mode;
        s->object = event->object;
        s->kind = 0;
        if (event->kind == 300) {
            s->kind = 1;
        }
        animation = 5;
        if (s->mode) {
            animation = 0;
        }
        s->transition = func_080E03F8(s->object, data_083A2C54, animation, 7, 0,
                                      task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        s->transition = func_080E05DC(s->transition);
        if (s->transition) {
            break;
        }
        if (!func_080DD494(s->object)) {
            s->unknown_20 = func_080DD214(func_080DD47C(s->object), 0, 0,
                                          task);
            event->state = 0x103;
            break;
        }
        s->count = func_080D8858(s->object, 0);
        if (!s->count) {
            event->state = 2;
            break;
        }
        s->delay = 1;
        event->state++;
        break;
    case 0x101:
        s->delay--;
        if (s->delay) {
            break;
        }
        s->unknown_1c = func_080DD4A4(s->object, s->index);
        func_080DD4C4();
        func_080DB838();
        event->state++;
    case 0x102:
        if (func_080D8B4C()) {
            break;
        }
        func_080E0570(s->children, 4);
        slot = s->index & 3;
        child.index = s->index;
        child.kind = s->kind;
        child.unknown_04 = s->unknown_1c;
        s->children[slot] = func_08005B6C(func_0810E738, 44, &child, task);
        s->index++;
        if (s->index == s->count) {
            event->state++;
            break;
        }
        s->delay = 76;
        event->state = 0x101;
        break;
    case 0x103:
        if (!func_080E0570(s->children, 4)) {
            break;
        }
        s->unknown_20 = func_080DBA5C(s->unknown_20);
        if (s->unknown_20) {
            break;
        }
        event->state = 2;
        break;
    }
    return 0;
}
