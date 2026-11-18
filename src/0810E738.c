#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *actor;
    u8 unknown_08[12];
    u16 index;
    u16 kind;
} Descriptor;

typedef struct {
    u8 index;
    u8 layer;
    u8 palette;
    u8 kind;
    s16 x;
    s16 y;
    void *actor;
    void *position;
    u8 coordinate_output[8];
    void *coordinate_task;
    void *blend_task;
    void *layer_task;
    void *actor_task;
    void *record_task;
} Payload;

extern u16 data_03003860[][16];
extern const u8 data_088F46F0[];
extern const u8 data_08949F68[];
extern const u8 data_0894CE14[];
extern const u8 data_0894D69C[];
extern const u8 data_083A2C90[];
extern const u8 data_083A2CFC[];
extern const u8 data_083A2CC0[][20];

extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_0814186C(const void *, void *, u32);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void func_080D47DC(void *, u16);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D3F84(void *, u8, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DD5EC(const void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern u32 func_080035A8(u8);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810E738(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        payload->index = descriptor->index;
        payload->kind = descriptor->kind;
        payload->actor = descriptor->actor;
        payload->layer = 2;
        if (payload->index & 1)
            payload->layer = 3;
        /* At 0810E78A the palette store precedes a fresh byte load and
         * second parity mask at 0810E792. Both index parities use bank 6. */
        payload->palette = 6;
        if (payload->index & 1)
            payload->palette = 6;
        payload->position = func_080DD748(payload->actor, &payload->x,
                                          &payload->y, 0);
        {
            u16 fill = 0;
            func_0814186C(&fill, data_03003860[payload->palette], 0x01000010);
        }
        break;
    }
    case 0x100: {
        u8 kind;
        s32 flags;
        /* 0810E866..0810E86C combines the two effect flags in the
         * outgoing fifth argument. */
        flags = 4;
        func_080D7220(data_088F46F0, 0, payload->layer, payload->x,
                      (s16)(payload->y - 4), 0);
        if (payload->kind == 0)
            payload->layer_task = func_080D4704(data_08949F68, task);
        else
            payload->layer_task = func_080D4704(data_0894CE14, task);
        func_080D47DC(payload->layer_task, payload->palette);
        payload->blend_task = func_080D3E9C(data_0894D69C, task);
        func_080D3F84(payload->blend_task, 12, 255);
        payload->coordinate_task = func_080D6098(payload->x, (s16)(payload->y - 4),
            0, 1, 2, payload->coordinate_output, data_083A2C90, task);
        payload->record_task = func_080DFD8C(data_083A2CFC, 1, 12, 0, task);
        kind = payload->kind;
        if (kind == 1 && func_080DD5EC(payload->actor))
            kind = 2;
        payload->actor_task = func_080DCFE4(payload->actor, data_083A2CC0[kind],
                                            12, 60, flags | 8, task, 60);
        descriptor->phase++;
        break;
    }
    case 0x101: {
        u8 had_layer_task;
        payload->blend_task = func_080D3F08(payload->blend_task);
        if (payload->blend_task)
            break;
        had_layer_task = payload->layer_task != 0;
        payload->layer_task = func_080D4774(payload->layer_task);
        if (payload->layer_task)
            break;
        if (had_layer_task) {
            u32 mask = func_080035A8(payload->layer);
            g_control_flags_03000940.display &= ~mask;
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (!payload->coordinate_task)
            descriptor->phase++;
        break;
    }
    case 0x102:
        payload->actor_task = func_080DBA5C(payload->actor_task);
        if (!payload->actor_task)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
