#include "control_flags.h"

// Target: complete [0x08119914, 0x08119C86), 882 bytes, 441 instructions.
// Local offset views; original declarations and full extents are unknown.
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 variant;
} Descriptor08119914;

typedef struct {
    s16 x;
    s16 y;
} Offset08119914;

typedef struct {
    u8 variant;
    u8 unknown_01[3];
    s16 x;
    s16 y;
    u8 ready;
    u8 unknown_09[3];
    void *actor;
    void *object;
    void *coordinate_child;
    void *target;
    void *initial_child;
    u8 coordinate_output[8];
    void *movement_child;
    void *sprite;
    void *timeline;
    void *window_children[2];
    void *window_child;
    void *record_child;
    void *wrapper_child;
    void *script_child;
} Payload08119914;

extern const u8 data_083A6410[];
extern const u8 data_083A649C[];
extern const u8 data_088F58E0[];
extern const u8 data_0894D69C[];
extern const u8 data_0894BE84[];
extern const u8 data_0894BEAC[];
extern const u8 data_083A64A4[];
extern const u8 data_083A64A0[];
extern const u8 data_083A64B4[];
extern const u8 data_088F06B0[];
extern const u8 data_0894DAA0[];
extern const u8 data_083A6458[];
extern const u8 data_0894ABF0[];
extern const u8 data_083A64AC[];
extern const u8 data_083A6488[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                          u16, u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern s8 func_080DBC88(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D48DC(void **, u16);
extern void *func_080D3F08(void *);
extern u16 func_080035A8(u8);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, u8, u8 *, const void *, u16, u16, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_080D3F84(void *, u8, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern void *func_080DF9E4(void *, u16, u16, void *);
extern void *func_080DBA5C(void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080DE1F0(void *);

u32 func_08119914(void *task, Descriptor08119914 *descriptor,
                  Payload08119914 *payload)
{
    switch (descriptor->phase) {
    case 0:
        {
            u8 animation;

            payload->variant = descriptor->variant;
            payload->actor = descriptor->actor;
            animation = 6;
            if (payload->variant != 0)
                animation = 0;
            payload->initial_child = func_080E03F8(payload->actor,
                data_083A6410, animation, 0, 0, task);
        }
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        payload->wrapper_child = func_080DDF68(payload->actor,
            &payload->object, 84, 1, &payload->ready,
            data_083A649C, 2, 0, task);
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        descriptor->phase++;
        break;
    case 0x101:
        {
            Offset08119914 offsets[4] = {
                {4, -2}, {4, -2}, {-4, -2}, {-4, -2}
            };

            if (payload->ready == 0)
                break;
            {
                s8 facing = func_080DBC88(payload->object);

                func_080D7220(data_088F58E0, 0, 2,
                    payload->x + offsets[facing].x,
                    payload->y + offsets[facing].y, 0);
            }
            payload->timeline = func_080D3E9C(data_0894D69C, task);
            payload->window_children[0] = func_080D4704(data_0894BE84, task);
            payload->window_children[1] = func_080D4704(data_0894BEAC, task);
            payload->script_child = func_080DFD8C(data_083A64A4, 1, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (!func_080D48DC(payload->window_children, 2))
            break;
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_080DE3BC(payload->object, 0);
        func_080DBA50(payload->wrapper_child);
        payload->wrapper_child = func_080DE4F4(payload->object, 1,
            &payload->ready, data_083A64A0, 0, 0, task);
        payload->target = func_080DD4A4(payload->actor, 0);
        payload->coordinate_child = func_080DD748(payload->target,
            &payload->x, &payload->y, 0);
        payload->script_child = func_080DFD8C(data_083A64B4, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (payload->ready == 0)
            break;
        func_080D49FC(1, 3, 0, payload->x, payload->y);
        payload->sprite = func_080D4B64(1, data_088F06B0, 796, 7);
        g_control_flags_03000940.display |= func_080035A8(3);
        payload->timeline = func_080D3E9C(data_0894DAA0, task);
        func_080D3F84(payload->timeline, 8, 255);
        payload->movement_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->coordinate_output, data_083A6458, task);
        payload->window_child = func_080D4724(data_0894ABF0, task, 20);
        payload->script_child = func_080DFD8C(data_083A64AC, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x104:
        payload->sprite = func_080D4D2C(payload->sprite, 1);
        if (payload->sprite != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->window_child = func_080D4774(payload->window_child);
        if (payload->window_child != 0)
            break;
        payload->movement_child = func_080D6134(payload->movement_child);
        if (payload->movement_child != 0)
            break;
        payload->record_child = func_080DF9E4(payload->target, 11, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        payload->record_child = func_080DBA5C(payload->record_child);
        if (payload->record_child != 0)
            break;
        payload->record_child = func_080DCFE4(payload->target,
            data_083A6488, 12, 0, 12, task, 0);
        descriptor->phase++;
        break;
    case 0x106:
        if (func_080DE1F0(payload->object)) {
            payload->record_child = func_080DBA5C(payload->record_child);
            if (payload->record_child == 0)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
