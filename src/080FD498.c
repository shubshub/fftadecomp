#include "ffta.h"
#include "effect_task.h"

/* Complete target [0x080FD498, 0x080FD6E8): 592 bytes. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080FD498;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation080FD498;

typedef struct {
    u16 counter;
    u8 flag;
    u8 status;
    u16 unknown_04;
    s16 x;
    s16 y;
    u16 unknown_0A;
    void *preparation_child;
    u32 unknown_10;
    void *coordinate_result;
    void *actor_state;
    u32 unknown_1C;
    void *coordinate_child;
    void *first_task;
    void *second_task;
    void *display;
    void *actor;
    void *initial_child;
    u32 unknown_38;
    void *transition_child;
    void *retained_child;
    Interpolation080FD498 vertical;
} Payload080FD498;

extern u16 g_control_flags_03000940;
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080FDE58(void *, u8, u8, u8 *, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D7220(const void *, u8, u8, s32, s32, u16);
extern void *func_080D979C(s32, s32, s32, const void *, void *);
extern void func_080E0608(Interpolation080FD498 *, s16, s16, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DD580(const void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4704(const void *, void *);

extern u8 func_080E0690(Interpolation080FD498 *);
extern void func_080E064C(Interpolation080FD498 *);
extern void func_080D7468(const void *, u8, s32, s32);
extern void *func_080D4774(void *);
extern void *func_080FDEBC(void *);
extern void *func_080D3F08(void *);
extern u32 func_080035A8(u8);
extern void *func_080D9B64(void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080FD498(void *task, Descriptor080FD498 *descriptor,
                  Payload080FD498 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 mode;
        void *actor;

        payload->flag = descriptor->flag;
        actor = descriptor->actor;
        payload->actor = actor;
        mode = 4;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_child = func_080E03F8(actor,
            (const void *)0x0839D68C, mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        payload->preparation_child = func_080FDE58(payload->actor, 3, 0,
            &payload->status, task);
        if (payload->preparation_child == 0)
            descriptor->phase = 2;
        else
            descriptor->phase++;
        break;
    case 0x101:
        if (payload->status == 0)
            break;
        if (payload->status == 2) {
            descriptor->phase = 0x103;
            break;
        }
        payload->actor_state = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(payload->actor_state,
            &payload->x, &payload->y, 0);
        payload->first_task = func_080D3E9C((const void *)0x0894DA60, task);
        func_080D7220((const void *)0x088F5AB4, 0, 2,
                      payload->x, (s16)(payload->y - 32), 0);
        payload->display = func_080D979C(0, 2, 0,
            (const void *)0x0839D6D4, task);
        func_080E0608(&payload->vertical, 32, 48, 120);
        payload->counter = 90;
        payload->retained_child = func_080DFD8C((const void *)0x0839D6EC,
            1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->counter != 0) {
            if (--payload->counter == 0) {
                if (func_080DD580(payload->actor_state)) {
                    payload->coordinate_child = func_080D6098(payload->x,
                        payload->y, 0, 1, 1, &payload->unknown_1C,
                        (const void *)0x0839D6BC, task);
                    payload->retained_child = func_080DFD8C(
                        (const void *)0x0839D6F4, 1, 4, 0, task);
                    payload->second_task = func_080D4704(
                        (const void *)0x0894AC40, task);
                }
                payload->transition_child = func_080DCFE4(payload->actor_state,
                    (const void *)0x0839D6D8, 12, 20, 4, task, 0);
            }
        }
        if (!func_080E0690(&payload->vertical)) {
            func_080E064C(&payload->vertical);
            func_080D7468((const void *)0x088F5AB4, 2, payload->x,
                          (s16)(payload->y - payload->vertical.current));
        } else {
            descriptor->phase++;
        }
        break;
    case 0x103:
        payload->second_task = func_080D4774(payload->second_task);
        if (payload->second_task != 0)
            break;
        payload->preparation_child = func_080FDEBC(payload->preparation_child);
        if (payload->preparation_child != 0)
            break;
        payload->first_task = func_080D3F08(payload->first_task);
        if (payload->first_task != 0)
            break;
        {
            u32 mask = func_080035A8(2);
            g_control_flags_03000940 &= ~mask;
        }
        payload->display = func_080D9B64(payload->display);
        if (payload->display != 0)
            break;
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->transition_child = func_080DBA5C(payload->transition_child);
        if (payload->transition_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
