#include "ffta.h"

// Target: complete [0x0811802C, 0x0811836C), 832 bytes, 416 instructions.

typedef struct {
    u16 phase;
    u8 unknown_02[0x14];
    u16 flag;
    u8 unknown_18[0x0C];
} Descriptor;

typedef struct {
    u16 x;
    u16 y;
} Point;

typedef struct {
    u16 timer;
    u8 index;
    u8 count;
    u8 flag;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 unknown_0A[2];
    void *task_0c;
    void *task_10;
    u8 unknown_14[4];
    void *object_18;
    u8 unknown_1C[8];
    void *task_24;
    u8 unknown_28[4];
    void *task_2c;
    u8 unknown_30[4];
    void *task_34;
    void *owner;
    void *slots[4];
    void *effect;
    u8 unknown_50[4];
} Payload;

typedef struct {
    u32 unknown[7];
} Request;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern const u8 data_083A5144[];
extern const u8 data_083A6000[];
extern const u8 data_083A51A4[];
extern const u8 data_083A51D4[];
extern const u8 data_083A6018[];
extern const u8 data_083A5FEC[];
extern const u8 data_083A6028[];
extern u16 data_03003920[];

extern u32 func_081179B4(void *task, void *descriptor, void *payload);
extern u32 func_08117B9C(void *task, void *descriptor, void *payload);
extern void func_0801E6F0(u16 *x, u16 *y);
extern void *func_080E03F8(void *, const void *, u8, u8, void *, void *);
extern u8 func_080DD494(void *);
extern void *func_080DD4B4(void *, u8);
extern void func_080DE268(void *);
extern void func_0814186C(const void *, void *, u32);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_08005B6C(TaskCallback, u16, void *, void *);
extern void *func_080D6134(void *);
extern void *func_080E051C(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern u8 func_080DB838(void *);
extern u8 func_080D8B4C(void);
extern u8 func_080DBAB8(void **, u32);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DD580(void *);

u32 func_0811802C(void *task, Descriptor *descriptor, Payload *payload)
{
    u16 pos[4];
    u16 *second, *fill_a, *fill_b;
    u16 effect_mode;
    Request sched_a, sched_b;
    Point point;
    u16 flag;
    u8 mode;
    u8 i;

    switch (descriptor->phase) {
    case 0:
        flag = descriptor->flag;
        payload->flag = flag;
        payload->owner = *(void **)((u8 *)descriptor + 4);
        mode = 8;
        if ((u8)flag != 0)
            mode = 0;
        second = &pos[1];
        func_0801E6F0(pos, second);
        point.x = pos[0];
        point.y = *second - 0x20;
        payload->task_34 = func_080E03F8(payload->owner, data_083A5144, mode, 6, &point, task);
        payload->count = func_080DD494(payload->owner);
        for (i = 0; i < payload->count; i++)
            func_080DE268(func_080DD4B4(payload->owner, i));
        fill_a = &pos[2];
        fill_b = &pos[3];
        *fill_a = 0x56E;
        func_0814186C(fill_a, data_03003920, 0x01000010);
        *fill_b = 0;
        func_0814186C(fill_b, data_03003920 + 0x10, 0x01000010);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->task_34 = func_080E05DC(payload->task_34);
        if (payload->task_34 == 0) {
            payload->effect = func_080DFD8C(data_083A6000, 3, 4, 0, task);
            payload->x = 0x78;
            payload->y = 0x50;
            payload->task_24 = func_080D6098(0x78, 0x50, 0, 1, 2, (u8 *)payload + 0x1C, data_083A51A4, task);
            payload->timer = 0x42;
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->timer--;
        if (payload->timer == 0) {
            payload->task_0c = func_08005B6C(func_081179B4, 0x30, &sched_a, task);
            payload->task_2c = func_080D6098(payload->x, payload->y, 0, 1, 1, (u8 *)payload + 0x28, data_083A51D4, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->task_24 = func_080D6134(payload->task_24);
        if (payload->task_24 != 0)
            break;
        payload->task_2c = func_080D6134(payload->task_2c);
        if (payload->task_2c != 0)
            break;
        payload->task_0c = func_080E051C(payload->task_0c);
        if (payload->task_0c != 0)
            break;
        descriptor->phase++;
        break;
    case 0x103:
        payload->effect = func_080DFD8C(data_083A6018, 2, 4, 0, task);
        payload->task_10 = func_08005B6C(func_08117B9C, 0x174, &sched_b, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->task_10 = func_080E051C(payload->task_10);
        if (payload->task_10 == 0) {
            payload->timer = 1;
            descriptor->phase++;
        }
        break;
    case 0x105:
        payload->timer--;
        if (payload->timer != 0)
            break;
        payload->object_18 = func_080DD4A4(payload->owner, payload->index);
        func_080DB838(func_080DD4C4(payload->object_18));
        descriptor->phase++;
    case 0x106:
        if (func_080D8B4C())
            break;
        func_080DBAB8(payload->slots, 4);
        i = (payload->index & 1) ? 4 : 2;
        payload->slots[payload->index & 3] =
            func_080DCFE4(payload->object_18, data_083A5FEC,
                          12 - (payload->index & 6), 10, i, task, 10);
        if (func_080DD580(payload->object_18)) {
            effect_mode = (payload->index & 1) ? 0x10 : 8;
            payload->effect = func_080DFD8C(data_083A6028, 1, effect_mode | 4, 10, task);
        }
        payload->index++;
        if (payload->index == payload->count) {
            descriptor->phase++;
        } else {
            payload->timer = 0x28;
            descriptor->phase = 0x105;
        }
        break;
    case 0x107:
        if (func_080DBAB8(payload->slots, 4))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
