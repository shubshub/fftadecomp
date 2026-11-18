#include "ffta.h"
#include "effect_task.h"

/* 0x080F897C..0x080F8C36: 698 bytes. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[14];
    u16 mode;
} Descriptor080F897C;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04;
    u8 mode;
    u8 ready;
    u8 unknown_07;
    u16 countdown;
    u16 unknown_0a;
    u32 unknown_0c[2];
    void *coordinate_child;
    void *first_child;
    void *second_child;
    u32 unknown_20;
    void *object;
    void *coordinate_result;
    void *third_child;
    void *source;
    void *initial_child;
    void *animation_child;
    void *object_child;
    void *record_child;
} Payload080F897C;

extern const u8 data_0839C168[];
extern const u8 data_088EF398[];
extern const u8 data_0894D90C[];
extern const u8 data_0839C1A4[];
extern const u8 data_0894AAB0[];
extern const u8 data_0839C208[];
extern const u8 data_0839C200[];
extern const u8 data_0839C1BC[];
extern const u8 data_0839C1EC[];
extern const u8 data_0839C210[];
extern u16 g_control_flags_03000940;
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u32 func_080DD47C(void *);
extern void func_080DBDC8(const void *, s16 *, s16 *);
extern u8 func_080D3B54(void *);
extern void func_080DE10C(void *, u16);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern u8 func_080DBFFC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);

extern void *func_080DBA5C(void *);

u32 func_080F897C(void *task, Descriptor080F897C *descriptor,
                  Payload080F897C *payload)
{
    u8 mode;
    void *object;
    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->source = descriptor->object;
        mode = 5;
        if (payload->mode != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->source,
            data_0839C168, mode, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        payload->object = (void *)func_080DD47C(payload->source);
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        if (func_080D3B54(payload->source)) {
            descriptor->phase = 2;
            break;
        }
        func_080DE10C(payload->object, 0x24);
        func_080D49FC(0, 2, 0, payload->x, payload->y);
        payload->first_child = func_080D4B64(0, data_088EF398, 0x3bf, 6);
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        payload->second_child = func_080D3E9C(data_0894D90C, task);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 1, payload->unknown_0c, data_0839C1A4, task);
        payload->third_child = func_080D4724(data_0894AAB0, task, 15);
        payload->record_child = func_080DFD8C(data_0839C208, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->first_child = func_080D4D2C(payload->first_child, 0);
        if (payload->first_child != 0)
            break;
        payload->second_child = func_080D3F08(payload->second_child);
        if (payload->second_child != 0)
            break;
        payload->third_child = func_080D4774(payload->third_child);
        if (payload->third_child != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->animation_child = func_080DDF68(payload->source,
            &payload->object, 0x8007, 2, &payload->ready, data_0839C200,
            0, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->ready == 0)
            break;
        func_080DBFFC(payload->source, 0);
        payload->countdown = 4;
        descriptor->phase++;
    case 0x103:
        if (payload->countdown != 0) {
            payload->countdown--;
            if (payload->countdown != 0)
                break;
        }
        if (func_080D8B4C())
            break;
        if (func_080D8858(payload->source, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->source, 0);
        payload->coordinate_result = func_080DD748(object, &payload->x, &payload->y, 0);
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_0c, data_0839C1BC, task);
        payload->object_child = func_080DCFE4(object, data_0839C1EC,
            12, 20, 2, task, 20);
        payload->record_child = func_080DFD8C(data_0839C210, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->object_child = func_080DBA5C(payload->object_child);
        if (payload->object_child == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
