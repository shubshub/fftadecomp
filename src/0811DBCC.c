#include "ffta.h"

/* Target: complete [0x0811DBCC, 0x0811DDF0), 548 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *first_object;
    void *second_object;
} Descriptor0811DBCC;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Motion0811DBCC;

typedef struct {
    u16 delay;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *first_object;
    void *second_object;
    void *coordinate_task;
    u8 coordinate_data[0x18];
    void *resource_task;
    void *timeline_task;
    void *initial_task;
    void *record_task;
    Motion0811DBCC motion;
} Payload0811DBCC;

extern const u8 data_083A711C[];
extern const u8 data_088F668C[];
extern const u8 data_0894DDD0[];
extern const u8 data_083A7170[];
extern const u8 data_083A7218[];
extern const u8 data_088F46F0[];
extern const u8 data_0894D690[];
extern const u8 data_0894CB14[];
extern const u8 data_083A7200[];
extern u16 g_control_flags_03000940;
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D7A70(const void *, u8, void *);
extern void func_080D35D8(void);
extern void *func_080D7ABC(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080E0608(Motion0811DBCC *, s16, s16, s16);
extern void func_080E064C(Motion0811DBCC *);
extern void func_080D7468(const void *, u8, s16, s16);
extern void *func_080D3F08(void *);
extern void *func_080D6134(void *);
extern u8 func_080E0690(Motion0811DBCC *);
extern void *func_080D4704(const void *, void *);
extern u32 func_080035A8(u8);
extern void func_080DBEB4(void *, u8);
extern void *func_080D4774(void *);

u32 func_0811DBCC(void *task, Descriptor0811DBCC *descriptor,
                  Payload0811DBCC *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->first_object = descriptor->first_object;
        payload->second_object = descriptor->second_object;
        func_080DBDC8(payload->first_object, &payload->x, &payload->y);
        payload->initial_task = func_080D7A70(data_083A711C, 7, task);
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        {
            void *initial_task;

            initial_task = func_080D7ABC(payload->initial_task);
            payload->initial_task = initial_task;
            if (initial_task)
                break;
            func_080D7220(data_088F668C, 1, 3, payload->x,
                (s16)(payload->y - 16), (u32)initial_task);
            payload->resource_task = func_080D3E9C(data_0894DDD0, task);
            payload->coordinate_task = func_080D6098(payload->x, payload->y,
                0, 1, 6, payload->coordinate_data, data_083A7170, task);
            payload->record_task = func_080DFD8C(data_083A7218,
                1, 4, 0, task);
            func_080E0608(&payload->motion, (s16)(payload->y - 16),
                payload->y, 60);
            descriptor->phase++;
        }
        break;
    case 0x101:
        func_080E064C(&payload->motion);
        func_080D7468(data_088F668C, 3, payload->x, payload->motion.current);
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        {
            void *coordinate_task;

            coordinate_task = func_080D6134(payload->coordinate_task);
            payload->coordinate_task = coordinate_task;
            if (coordinate_task)
                break;
            if (!func_080E0690(&payload->motion))
                break;
            func_080D7220(data_088F46F0, 0, 2, payload->x,
                (s16)(payload->y - 10), (u32)coordinate_task);
        }
        payload->resource_task = func_080D3E9C(data_0894D690, task);
        payload->timeline_task = func_080D4704(data_0894CB14, task);
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->coordinate_data, data_083A7200, task);
        payload->delay = 60;
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->delay == 60) {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
        }
        if (payload->delay != 0 && --payload->delay == 0) {
            func_080DBEB4(payload->first_object, 1);
            func_080DBEB4(payload->second_object, 1);
        }
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task)
            break;
        payload->timeline_task = func_080D4774(payload->timeline_task);
        if (payload->timeline_task)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        descriptor->phase = 2;
        break;
    }
    return 0;
}
