#include "ffta.h"

// Target 0x080ECD8C, complete [0x080ECD8C, 0x080ED042), 694 bytes.

typedef struct {
    u32 unknown_00[5];
    s16 x;
    s16 y;
    u32 unknown_18;
} Descriptor080ECD8C;

typedef struct {
    u16 state;
    u16 unknown_02;
    void *resource;
    u8 unknown_08[14];
    u16 mode;
} Event080ECD8C;

typedef struct {
    u16 timer;
    u16 index;
    u8 mode;
    u8 unknown_05;
    s16 x;
    s16 y;
    u16 unknown_0A;
    void *task_0C;
    void *task_10;
    void *task_14;
    void *object_18;
    void *resource;
    void *object_20;
    void *object_24;
    void *object_28;
    void *object_2C;
} State080ECD8C;

typedef struct {
    s16 x;
    s16 y;
} Position080ECD8C;

typedef struct {
    u8 unknown_00;
    u8 unknown_01;
    u8 first;
    u8 second;
} Step080ECD8C;

typedef struct {
    u8 unknown_00;
    u8 unknown_01;
    u8 step;
} TaskState080ECD8C;

extern u8 data_083990C8[];
extern u8 data_0839923C[];
extern const Step080ECD8C data_08399160[];
extern u8 data_0894D710[];

extern void *func_080DD47C(void *resource);
extern void func_080DBDEC(u8 selector, void *argument, s16 *first_output,
                          s16 *second_output, s16 *third_output);
extern void *func_080E03F8(void *, const void *, u8, u8, Position080ECD8C *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080DFD68(u8, u16, void *);
extern void *func_080DFED8(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_08005B6C(void *callback, u32 size,
                           Descriptor080ECD8C *descriptor, void *parent);
extern TaskState080ECD8C *func_08005BFC(void *task);
extern void func_08005B58(void *task);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void func_0801E5E0(s16 x, s16 y);
extern void func_080DFE28(u8, u16);
extern void func_080EDB80(void *resource);
extern u8 func_080D8858(void *, u16);
extern void *func_080EDB98(void *, u16, void *);
extern void *func_080EDBDC(void *);
extern u32 func_080EC7DC(void);
extern u32 func_080EC6D8(void);
extern u32 func_080ECCDC(void);

u32 func_080ECD8C(void *owner, Event080ECD8C *event, State080ECD8C *s)
{
    s16 x;
    s16 y;
    s16 z;
    Position080ECD8C position;
    TaskState080ECD8C *task_state;

    switch (event->state) {
    case 0:
        s->mode = event->mode;
        s->resource = event->resource;
        if (s->mode == 0) {
            func_080DBDEC(6, func_080DD47C(s->resource), &x, &y, &z);
            x -= 120;
            y -= 80;
            x &= ~7;
            y &= ~7;
            position.x = x;
            position.y = y;
            s->object_20 = func_080E03F8(s->resource, data_083990C8, 3, 6,
                                         &position, owner);
            s->x = x;
            s->y = y;
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (s->mode) {
            s->object_20 = func_080E05DC(s->object_20);
            if (s->object_20 == 0)
                event->state = 0x106;
        } else {
            s->object_2C = func_080DFD68(1, 30, owner);
            event->state++;
        }
        break;
    case 0x101: {
        Descriptor080ECD8C descriptor;

        s->object_20 = func_080E05DC(s->object_20);
        if (s->object_20 != 0)
            break;
        s->object_2C = func_080DFED8(s->object_2C);
        if (s->object_2C != 0)
            break;
        descriptor.x = s->x;
        descriptor.y = s->y;
        s->task_10 = func_08005B6C(func_080EC7DC, 0x1060, &descriptor, owner);
        s->task_0C = func_08005B6C(func_080EC6D8, 0x94, &descriptor, owner);
        s->object_28 = func_080DFD8C(data_0839923C, 1, 4, 0, owner);
        s->timer = 120;
        event->state++;
        break;
    }
    case 0x102: {
        Descriptor080ECD8C second;

        if (--s->timer != 0)
            break;
        s->task_14 = func_08005B6C(func_080ECCDC, 0x24, &second, owner);
        s->timer = 1;
        event->state++;
        break;
    }
    case 0x103:
        if (--s->timer != 0)
            break;
        task_state = func_08005BFC(s->task_10);
        task_state->unknown_00 = 1;
        task_state->step = s->index;
        s->timer = data_08399160[s->index].first + data_08399160[s->index].second;
        s->index++;
        if (s->index != 11)
            break;
        s->object_18 = func_080D3E9C(data_0894D710, owner);
        s->timer = 30;
        event->state++;
        break;
    case 0x104:
        if (--s->timer != 0)
            break;
        func_08005B58(s->task_0C);
        s->task_0C = 0;
        func_08005B58(s->task_10);
        s->task_10 = 0;
        func_08005B58(s->task_14);
        s->task_14 = 0;
        func_0801E5E0(s->x, s->y);
        s->object_2C = func_080DFD68(0, 30, owner);
        func_080DFE28(1, 32);
        func_080EDB80(s->resource);
        event->state++;
        break;
    case 0x105:
        s->object_18 = func_080D3F08(s->object_18);
        if (s->object_18 != 0)
            break;
        s->object_2C = func_080DFED8(s->object_2C);
        if (s->object_2C != 0)
            break;
        if (func_080D8858(s->resource, 0))
            event->state++;
        else
            event->state = 2;
        break;
    case 0x106:
        s->object_24 = func_080EDB98(s->resource, 6, owner);
        event->state++;
        break;
    case 0x107:
        s->object_24 = func_080EDBDC(s->object_24);
        if (s->object_24 == 0)
            event->state = 2;
        break;
    }
    return 0;
}
