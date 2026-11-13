// Target: complete [0x0811AE00, 0x0811AF96), 406 bytes.
#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[14];
    u16 flag;
} Descriptor0811AE00;

typedef struct {
    s16 x;
    s16 y;
    u16 countdown;
    u8 flag;
    u8 active;
    void *first_task;
    void *second_task;
    void *actor;
    void *object;
    void *resource;
    u8 unknown_1c[8];
    void *window;
    void *overlay;
    void *effect;
} Payload0811AE00;

typedef struct {
    u8 unknown[0x1C];
} TaskDescriptor0811AE00;

extern u16 data_03003A80[];
extern const u8 data_083A6810[];
extern const u8 data_083A6834[];
extern const u8 data_083A684C[];
extern const u8 data_083A6854[];
extern void *func_08005B6C(TaskCallback, u16, void *, void *);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_081482D4(const u16 *, u16 *, u16, u8);
extern void *func_080DD47C(void *);
extern void func_080DE10C(void *, u16);
extern void *func_080DE4B0(void *, u8 *, int, int, int, int, int, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, u8 *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u8, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);
extern void *func_080E051C(void *);
extern u32 func_0811AB44(void *, void *, void *);
extern u32 func_0811ACF4(void *, void *, void *);

u32 func_0811AE00(void *task, Descriptor0811AE00 *descriptor,
                  Payload0811AE00 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        int mode;

        payload->flag = descriptor->flag;
        payload->object = descriptor->object;
        mode = 3;
        if (payload->flag)
            mode = 0;
        payload->resource = func_080E03F8(payload->object, data_083A6810,
                                          mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->resource = func_080E05DC(payload->resource);
        if (payload->resource == 0) {
            func_081482D4(data_03003A80, data_03003A80 + 0x60, 16, 6);
            payload->actor = func_080DD47C(payload->object);
            func_080DE10C(payload->actor, 60);
            payload->overlay = func_080DE4B0(payload->actor, &payload->active,
                                             1, -1, 0, 0x3a, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        if (payload->active != 0) {
            func_080DBDC8(payload->actor, &payload->x, &payload->y);
            payload->window = func_080D6098(payload->x, payload->y, 0, 1, 1,
                                            payload->unknown_1c,
                                            data_083A6834, task);
            payload->effect = func_080DFD8C(data_083A684C, 1, 4, 0, task);
            payload->countdown = 0x1c;
            descriptor->phase++;
        }
        break;
    case 0x102: {
        TaskDescriptor0811AE00 child_descriptor;

        if (payload->countdown != 0) {
            payload->countdown--;
            break;
        }
        payload->first_task = func_08005B6C(func_0811AB44, 0x30,
                                            &child_descriptor, task);
        payload->second_task = func_08005B6C(func_0811ACF4, 0x24,
                                             &child_descriptor, task);
        payload->effect = func_080DFD8C(data_083A6854, 1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x103:
        payload->window = func_080D6134(payload->window);
        if (payload->window == 0) {
            payload->overlay = func_080DBA5C(payload->overlay);
            if (payload->overlay == 0) {
                payload->first_task = func_080E051C(payload->first_task);
                if (payload->first_task == 0) {
                    payload->second_task = func_080E051C(payload->second_task);
                    if (payload->second_task == 0)
                        descriptor->phase = 2;
                }
            }
        }
        break;
    }
    return 0;
}
