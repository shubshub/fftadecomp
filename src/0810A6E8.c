#include "ffta.h"

/* Target 0x0810A6E8, complete [0x0810A6E8, 0x0810A84E), 358 bytes:
 * 318 code bytes, 36 literal bytes and four internal alignment bytes. */

/* Local access views; original declaration types and extents are unknown. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 mode;
    u16 variant;
} Descriptor0810A6E8;

typedef struct {
    u8 mode;
    u8 variant;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *actor;
    void *coordinate_result;
    void *sprite;
    void *resource_child;
    void *timeline_child;
    void *effect_child;
    void *record_child;
} Payload0810A6E8;

extern const u8 data_088F1870[];
extern const u8 data_0894D690[];
extern const u8 data_0894CB4C[];
extern const u8 data_083A1CAC[];
extern const u8 data_083A1C78[];
extern u16 g_control_flags_03000940;

/* Prototypes describe the values used at these call sites. */
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern u8 func_080DD580(void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u32 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D3F08(void *);
extern void *func_080D4D2C(void *, u8);
extern void *func_080D4774(void *);
extern void func_080D4020(void);
extern void *func_080DBA5C(void *);

u32 func_0810A6E8(void *task, Descriptor0810A6E8 *descriptor,
                  Payload0810A6E8 *payload)
{
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->variant = descriptor->variant;
        payload->actor = descriptor->actor;
        payload->coordinate_result = func_080DD748(payload->actor,
            &payload->x, &payload->y, 0);
        break;
    case 0x100:
        if (func_080DD580(payload->actor)) {
            func_080D49FC(0, 2, 0, payload->x, (s16)(payload->y - 12));
            payload->sprite = func_080D4B64(0, data_088F1870, 975, 6);
            {
                u32 mask = func_080035A8(2);
                u16 control = g_control_flags_03000940;
                control |= mask;
                g_control_flags_03000940 = control;
            }
            payload->resource_child = func_080D3E9C(data_0894D690, task);
            payload->timeline_child = func_080D4704(data_0894CB4C, task);
            flags = (payload->mode & 1) ? 16 : 8;
            payload->record_child = func_080DFD8C(data_083A1CAC, 1,
                flags | 4, 0, task);
        }
        flags = (payload->mode & 1) ? 4 : 2;
        payload->effect_child = func_080DCFE4(payload->actor,
            data_083A1C78, 12, 58, flags, task, 10);
        descriptor->phase++;
        break;
    case 0x101:
        payload->resource_child = func_080D3F08(payload->resource_child);
        if (payload->resource_child != 0)
            break;
        payload->sprite = func_080D4D2C(payload->sprite, 0);
        if (payload->sprite != 0)
            break;
        payload->timeline_child = func_080D4774(payload->timeline_child);
        if (payload->timeline_child != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        func_080D4020();
        descriptor->phase++;
        break;
    case 0x102:
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
