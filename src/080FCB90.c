#include "ffta.h"
#include "control_flags.h"

/* Target 0x080FCB90..0x080FCF68, 984 bytes including literal pools.  Task
 * callback in the family of func_080FC800 and func_080FD498: the same
 * descriptor, and a payload with the same coordinate block at +0x08..+0x18.
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    s16 classifier;
    u16 flag;
} Descriptor080FCB90;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation080FCB90;

typedef struct {
    u16 unknown_00;
    u8 flag;
    u8 mode;
    u8 status;
    u8 unknown_05[3];
    s16 x;
    s16 y;
    void *preparation_child;
    u32 unknown_10;
    void *coordinate_result;
    void *actor_state;
    void *objects[2];
    void *resource_child;
    void *effect;
    void *actor;
    void *initial_child;
    void *display_child;
    void *record_child;
    u32 unknown_3C;
    void *sound_child;
    Interpolation080FCB90 motion;
} Payload080FCB90;

extern const u8 data_0839D498[];
extern const u8 data_088EACD8[];
extern u8 data_0600F9C0[];
extern u8 data_06005000[];
extern u16 data_03003860[];
extern const u8 data_088F46CC[];
extern const u8 data_0839D4F0[];
extern const u8 data_08502C00[];
extern const u8 data_0894AAB0[];
extern const u8 data_0839D4C8[][20];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void *func_080FDE58(void *, u8, u8, u8 *, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080DC268(void *, const void *, const void *, u8, void *);
extern void func_080D72C8(const void *, u8, u8, s16, s16, u16, u8);
extern void *func_080DAB84(int, int, int, void *);
extern void func_080E0608(Interpolation080FCB90 *, s16, s16, s16);
extern void func_0801E610(u8 *first, u8 *second);
extern u16 func_080035D0(u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080E0690(Interpolation080FCB90 *);
extern void func_080E064C(Interpolation080FCB90 *);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern void func_080D9B98(void *);
extern void *func_080DBA5C(void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void *func_080D4704(const void *, void *);
extern u8 func_080D5F24(void **, u16);
extern void *func_080DC2F0(void *, u8, u16, void *);
extern void func_080DADFC(void *);
extern u32 func_080035A8(u8);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D4774(void *);
extern void *func_080FDEBC(void *);
extern void *func_080D9B64(void *);

u32 func_080FCB90(void *task, Descriptor080FCB90 *descriptor,
                  Payload080FCB90 *payload)
{
    u8 first;
    u8 second;

    switch (descriptor->phase) {
    case 0: {
        u8 mode;

        payload->mode = 0;
        if (descriptor->classifier == 0x146)
            payload->mode = 1;
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 4;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(payload->actor, data_0839D498,
            mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u8 kind;

        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        kind = 0;
        if (payload->mode == 1) {
            func_080D45D0(data_088EACD8, 6, 1, 1, 1);
            kind = 6;
        }
        payload->preparation_child = func_080FDE58(payload->actor, kind, 0,
            &payload->status, task);
        if (payload->preparation_child == 0)
            descriptor->phase = 2;
        else
            descriptor->phase++;
        break;
    }
    case 0x101:
        if (payload->status == 0)
            break;
        if (payload->status == 2) {
            descriptor->phase = 0x104;
            break;
        }
        payload->actor_state = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_state,
            &payload->x, &payload->y, 0);
        payload->display_child = func_080DC268(payload->coordinate_result,
            data_0600F9C0, data_06005000, 0, task);
        if (payload->mode == 1)
            data_03003860[0x61] = 0x16;
        func_080D72C8(data_088F46CC, 0, 2, 0, 0, 0, 1);
        payload->effect = func_080DAB84(0, 0, 0, task);
        func_080E0608(&payload->motion, 0, 24, 32);
        func_0801E610(&first, &second);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xa0;
        g_control_flags_03000940.winin_lo =
            0x3f & ~(func_080035D0(first) | func_080035D0(second));
        g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(2);
        g_control_flags_03000940.display |= 0x2000;
        payload->sound_child = func_080DFD8C(data_0839D4F0, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (!func_080E0690(&payload->motion)) {
            func_080E064C(&payload->motion);
            func_080DAC80(payload->effect, payload->x, payload->y,
                payload->motion.current, payload->motion.current >> 1);
            func_080D9B98(payload->effect);
            break;
        }
        payload->display_child = func_080DBA5C(payload->display_child);
        if (payload->display_child != 0)
            break;
        payload->objects[0] = func_080D5CC0(data_08502C00, 0, payload->x,
            payload->y, 0x3d4, 6, 0, 0);
        payload->objects[1] = func_080D5CC0(data_08502C00, 1, payload->x,
            payload->y, 0x3d4, 6, 1, 0);
        payload->resource_child = func_080D4704(data_0894AAB0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (!func_080D5F24(payload->objects, 2))
            break;
        func_080E0608(&payload->motion, 24, 0, 32);
        payload->display_child = func_080DC2F0(payload->coordinate_result, 0,
            12, task);
        descriptor->phase++;
        break;
    case 0x104:
        if (!func_080E0690(&payload->motion)) {
            func_080E064C(&payload->motion);
            func_080DADFC(payload->effect);
            func_080DAC80(payload->effect, payload->x, payload->y,
                payload->motion.current, payload->motion.current >> 1);
            func_080D9B98(payload->effect);
            if (func_080E0690(&payload->motion)) {
                g_control_flags_03000940.display &= ~func_080035A8(2);
                g_control_flags_03000940.display &= 0xdfff;
            }
            break;
        }
        payload->display_child = func_080DBA5C(payload->display_child);
        if (payload->display_child != 0)
            break;
        payload->record_child = func_080DCFE4(payload->actor_state,
            data_0839D4C8[payload->mode], 12, 0, 12, task, 0);
        descriptor->phase++;
        break;
    case 0x105:
        payload->resource_child = func_080D4774(payload->resource_child);
        if (payload->resource_child != 0)
            break;
        payload->preparation_child = func_080FDEBC(payload->preparation_child);
        if (payload->preparation_child != 0)
            break;
        payload->effect = func_080D9B64(payload->effect);
        if (payload->effect != 0)
            break;
        payload->record_child = func_080DBA5C(payload->record_child);
        if (payload->record_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
