#include "ffta.h"

/* Target: complete [0x0811D5FC, 0x0811D73A), 318 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *value;
} Descriptor0811D5FC;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *value;
    void *effect;
    void *timeline;
    void *first_child;
    void *second_child;
    void *animation_task;
    void *record_task;
} Payload0811D5FC;

extern const u8 data_088F1B54[];
extern const u8 data_0894D6A8[];
extern const u8 data_0894C9B0[];
extern const u8 data_0894AC90[];
extern const u8 data_083A70AC[];
extern u16 g_control_flags_03000940;
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080D49FC(u32, u32, u32, u32, u32);
extern void *func_080D4B64(u32, const void *, u32, u32);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D3F84(void *, u32, u32);
extern void *func_080D4704(const void *, void *);
extern void *func_080DBB14(void *, u32, u32, u32, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4D2C(void *, u32);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void func_080D4020(void);
extern void *func_080DBA5C(void *);

u32 func_0811D5FC(void *task, Descriptor0811D5FC *descriptor,
                  Payload0811D5FC *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->value = descriptor->value;
        func_080DBDC8(payload->value, &payload->x, &payload->y);
        break;
    case 0x100:
        func_080D49FC(1, 3, 0, 0, 0);
        payload->effect = func_080D4B64(1, data_088F1B54, 812, 7);
        {
            u32 mask = func_080035A8(3);
            u32 flags = g_control_flags_03000940;

            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->timeline = func_080D3E9C(data_0894D6A8, task);
        func_080D3F84(payload->timeline, 8, 255);
        payload->first_child = func_080D4704(data_0894C9B0, task);
        payload->second_child = func_080D4704(data_0894AC90, task);
        payload->animation_task = func_080DBB14(payload->value, 7, 12, 0, task);
        payload->record_task = func_080DFD8C(data_083A70AC, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101: {
        u32 mask;

        payload->effect = func_080D4D2C(payload->effect, 1);
        if (payload->effect != 0)
            break;
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child != 0)
            break;
        payload->second_child = func_080D4774(payload->second_child);
        if (payload->second_child != 0)
            break;
        mask = func_080035A8(3);
        g_control_flags_03000940 &= ~mask;
        func_080D4020();
        payload->animation_task = func_080DBA5C(payload->animation_task);
        if (payload->animation_task == 0)
            descriptor->phase++;
        break;
    }
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
