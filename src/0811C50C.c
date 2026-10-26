#include "ffta.h"

/* Target: complete [0x0811C50C, 0x0811C644), 312 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
} Descriptor0811C50C;

typedef struct {
    u8 unknown_00[0x34];
    u16 field_34;
} Object0811C50C;

typedef struct {
    u16 delay;
    u8 ready;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *object;
    void *resource_task;
    void *timeline_task;
    void *coordinate_task;
    void *record_task;
} Payload0811C50C;

extern const u8 data_083A6CE4[];
extern const u8 data_088F469C[];
extern const u8 data_0894C7A4[];
extern const u8 data_0894D69C[];
extern u16 g_control_flags_03000940;
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080DE3BC(void *, u8);
extern void *func_080DE4B0(void *, u8 *, u8, u8, u32, u32, u32, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D3F84(void *, u8, u8);
extern Object0811C50C *func_080DD350(void *);
extern void func_080DE10C(void *, u16);
extern u8 func_080DBC18(void *, u32);
extern void func_080DD720(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u32 func_080035A8(u8);
extern u8 func_080DE1F0(void *);

u32 func_0811C50C(void *task, Descriptor0811C50C *descriptor,
                  Payload0811C50C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->object = descriptor->object;
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        func_080DE3BC(payload->object, 0);
        payload->coordinate_task = func_080DE4B0(payload->object,
            &payload->ready, 2, 3, 0, 0, 0, task);
        payload->record_task = func_080DFD8C(data_083A6CE4, 1, 4, 0, task);
        break;
    case 0x100:
        if (payload->ready == 0)
            break;
        func_080D7220(data_088F469C, 1, 3, payload->x, payload->y, 0);
        payload->timeline_task = func_080D4704(data_0894C7A4, task);
        payload->resource_task = func_080D3E9C(data_0894D69C, task);
        func_080D3F84(payload->resource_task, 8, 255);
        payload->delay = 26;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->delay != 0)
            break;
        func_080DD350(payload->object)->field_34 = 0x74;
        func_080DE10C(payload->object, 0x24);
        func_080DBC18(payload->object, 0);
        func_080DD720(payload->object, 4);
        descriptor->phase++;
        break;
    case 0x102:
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        payload->timeline_task = func_080D4774(payload->timeline_task);
        if (payload->timeline_task)
            break;
        {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        if (func_080DE1F0(payload->object))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
