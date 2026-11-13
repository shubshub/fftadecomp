#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x0810AC28, 0x0810ADF4), 460 bytes, 189 instructions.

// Local access views; original declaration types and extents are unknown.
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 variant;
} Descriptor0810AC28;

typedef struct {
    u8 unknown_00[2];
    u8 variant;
    u8 mode;
    s16 x;
    s16 y;
    void *coordinate_result;
    void *effect_child;
    u8 unknown_10[8];
    void *first_child;
    void *second_child;
    void *initial_child;
    void *actor;
    void *record_child;
    void *object_child;
} Payload0810AC28;

extern const u8 data_083A1CCC[];
extern const u8 data_088F66A8[];
extern const u8 data_083A1CF0[];
extern const u8 data_0894CBA8[];
extern const u8 data_0894DDF0[];
extern const u8 data_083A1D20[];
extern const u8 data_083A1D34[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D6098(s16, s16, u8, u8, u8, void *, const void *, void *);
extern void func_080D61E4(void *, u8);
extern u16 func_080035D0(u8);
extern u32 func_080035A8(u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void func_080D6128(void *);
extern void *func_080DBA5C(void *);

u32 func_0810AC28(void *task, Descriptor0810AC28 *descriptor,
                  Payload0810AC28 *payload)
{
    u8 animation;
    void *actor_object;

    switch (descriptor->phase) {
    case 0:
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        animation = 3;
        if (payload->variant != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_child = func_080E03F8(payload->actor, data_083A1CCC,
            animation, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        actor_object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(actor_object,
            &payload->x, &payload->y, 0);
        func_080D7220(data_088F66A8, 1, 3, 0, 0, 0);
        payload->effect_child = func_080D6098(payload->x, payload->y, 0, 1,
            2, payload->unknown_10, data_083A1CF0, task);
        func_080D61E4(payload->effect_child, 1);
        g_control_flags_03000940.winout_lo = 63 & ~func_080035D0(3);
        g_control_flags_03000940.winout_hi = 63;
        g_control_flags_03000940.display |= 0x8000;
        payload->first_child = func_080D4704(data_0894CBA8, task);
        payload->second_child = func_080D3E9C(data_0894DDF0, task);
        payload->record_child = func_080DCFE4(actor_object, data_083A1D20,
            12, 80, 12, task, 80);
        payload->object_child = func_080DFD8C(data_083A1D34, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->second_child = func_080D3F08(payload->second_child);
        if (payload->second_child != 0)
            break;
        payload->first_child = func_080D4774(payload->first_child);
        if (payload->first_child != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        g_control_flags_03000940.display &= 0x7fff;
        if (payload->effect_child != 0) {
            func_080D6128(payload->effect_child);
            payload->effect_child = 0;
        }
        payload->record_child = func_080DBA5C(payload->record_child);
        if (payload->record_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
