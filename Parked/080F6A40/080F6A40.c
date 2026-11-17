#include "ffta.h"

// Target 0x080F6A40, complete [0x080F6A40, 0x080F6C46), 518 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 variant;
} Descriptor080F6A40;

typedef struct {
    u8 unknown_00;
    u8 variant;
    u8 ready;
    u8 unknown_03;
    u8 count;
    u8 countdown;
    u16 index;
    u8 unknown_08[12];
    void *coordinate_child;
    void *children[4];
    void *object;
    void *tasks[3];
    void *actor;
    void *initial_child;
    void *animation_child;
    void *record_child;
} Payload080F6A40;

typedef struct {
    u32 unknown_00;
    void *object;
    u8 unknown_08[12];
    u16 index;
    u8 unknown_16[6];
} Request080F6A40;

typedef u32 (*TaskCallback080F6A40)(void *, void *, void *);

extern const u8 data_0839B904[];
extern const u8 data_0839B9E4[];
extern const u8 data_0839B928[];
extern const u8 data_0839B9B8[];
extern const u8 data_0839B9E8[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void func_080D4870(const void *, void **, int, void *);
extern s8 func_080DBC88(void *);
extern void func_080D6194(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D8924(void *, u8, u16, void *);
extern u8 func_080E0570(void **, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_08005B6C(TaskCallback080F6A40, u16, void *, void *);
extern u32 func_080F695C(void *, void *, void *);
extern u8 func_080D48DC(void **, u16);
extern void *func_080D6134(void *);
extern u8 func_080DE1F0(void *);

u32 func_080F6A40(void *task, Descriptor080F6A40 *descriptor,
                  Payload080F6A40 *payload)
{
    s16 x;
    s16 y;
    u8 animation;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        animation = 3;
        if (payload->variant != 0)
            animation = 0;
        payload->initial_child = func_080E03F8(payload->actor, data_0839B904,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (payload->variant != 0) {
            payload->count = func_080DD494(payload->actor);
            payload->countdown = 1;
            descriptor->phase = 0x102;
            break;
        }
        payload->animation_child = func_080DDF68(payload->actor,
            &payload->object, 0x94, 1, &payload->ready, data_0839B9E4,
            0, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->ready == 0)
            break;
        func_080DBDC8(payload->object, &x, &y);
        payload->coordinate_child = func_080D6098(x, y, 0, 1, 3,
            payload->unknown_08, data_0839B928, task);
        func_080D4870(data_0839B9B8, payload->tasks, 3, task);
        if (func_080DBC88(payload->object) > 1)
            func_080D6194(payload->coordinate_child, 1);
        payload->record_child = func_080DFD8C(data_0839B9E8, 1, 4, 0, task);
        payload->count = func_080D8924(payload->actor, 0, 0x38, task);
        if (payload->count == 0) {
            descriptor->phase = 0x103;
            break;
        }
        payload->countdown = 0x15;
        descriptor->phase++;
        break;
    case 0x102:
        func_080E0570(payload->children, 4);
        if (--payload->countdown != 0)
            break;
        {
        Request080F6A40 request;
        request.index = payload->index;
        request.object = func_080DD4A4(payload->actor, payload->index);
        payload->children[payload->index] = func_08005B6C(func_080F695C,
            0x28, &request, task);
        payload->countdown = 0x1e;
        if (++payload->index == payload->count)
            descriptor->phase++;
        }
        break;
    case 0x103:
        if (func_080D48DC(payload->tasks, 3) == 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        if (func_080DE1F0(payload->object) == 0)
            break;
        if (func_080E0570(payload->children, 4) == 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
