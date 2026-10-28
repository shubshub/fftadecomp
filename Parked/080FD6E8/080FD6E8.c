#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[0x0e];
    u16 flag;
} Descriptor080FD6E8;

typedef struct __attribute__((packed)) {
    u8 value : 8;
    u8 mode : 8;
} Pair080FD6E8;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Interpolation080FD6E8;

typedef struct {
    u16 counter;
    u8 flag;
    u8 status;
    u16 unknown_04;
    s16 x;
    s16 y;
    Pair080FD6E8 pairs[160];
    u16 unknown_14a;
    void *actor_task;
    u32 unknown_150;
    void *coordinate_task;
    void *actor_state;
    void *first_task;
    void *second_task;
    void *first_display;
    void *second_display;
    void *actor;
    void *initial_task;
    void *effect_task;
    void *retained_task;
    Interpolation080FD6E8 vertical;
    Interpolation080FD6E8 horizontal;
} Payload080FD6E8;

extern const u8 data_0839D71C[];
extern const u8 data_0894DA74[];
extern const u8 data_088F5ADC[];
extern const u8 data_0839D740[];
extern const u8 data_0839D758[];
extern const u8 data_0839D744[];
extern const u8 data_089492DC[];
extern u16 g_control_flags_03000940;

extern void *func_080E03F8(void *, const void *, s32, s32, s32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080FDE58(void *, u8, u8, u8 *, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s32);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D7220(const void *, s32, s32, s32, s32, s32);
extern void *func_080D979C(s32, s32, s32, const void *, void *);
extern void *func_080D9A24(s32, s32, s32, const void *, void *);
extern void *func_080D9B08(void *);
extern void func_0814186C(const void *, void *, u32);
extern void func_080E0608(Interpolation080FD6E8 *, s16, s16, s16);
extern void *func_080DFD8C(const void *, s32, s32, s32, void *);
extern void *func_080DCFE4(void *, const void *, s32, s32, s32, void *, s32);
extern void *func_080D4704(const void *, void *);
extern void func_080E064C(Interpolation080FD6E8 *);
extern void func_080D9B98(void *);
extern void func_080D7468(const void *, s32, s32, s32);
extern u8 func_080E0690(Interpolation080FD6E8 *);
extern void func_080D9ADC(void *, s32, s32);
extern u32 func_080035A8(s32);
extern void *func_080D4774(void *);
extern void *func_080FDEBC(void *);
extern void *func_080D3F08(void *);
extern void *func_080D9B64(void *);
extern void *func_080DBA5C(void *);

/* 0x080FD6E8 .. 0x080FDAB0: 968 bytes, including literal pools. */
s32 func_080FD6E8(void *task, Descriptor080FD6E8 *descriptor,
                  Payload080FD6E8 *payload)
{
    u8 i;
    u8 j;
    u8 value;

    switch (descriptor->phase) {
    case 0: {
        s32 mode;
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        mode = 3;
        if (payload->flag != 0)
            mode = 0;
        payload->initial_task = func_080E03F8(payload->actor, data_0839D71C,
                                             mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        payload->actor_task = func_080FDE58(payload->actor, 4, 1,
                                           &payload->status, task);
        if (payload->actor_task == 0)
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
        payload->coordinate_task = func_080DD748(payload->actor_state,
                                                &payload->x, &payload->y, 0);
        payload->first_task = func_080D3E9C(data_0894DA74, task);
        func_080D7220(data_088F5ADC, 0, 2, payload->x, payload->y, 0);
        payload->first_display = func_080D979C(0, 2, 0, data_0839D740, task);
        for (i = 0; i < 64; i++) {
            payload->pairs[i].value = 12;
            payload->pairs[i].mode = 16;
        }
        for (value = 11; value != 0; value--) {
            for (j = 0; j < 3; j++) {
                payload->pairs[i].value = value;
                payload->pairs[i].mode = 16;
                i++;
            }
        }
        for (; i < 160; i++) {
            payload->pairs[i].value = 0;
            payload->pairs[i].mode = 16;
        }
        payload->second_display = func_080D9A24(0, 16, 0, 0, task);
        func_0814186C(payload->pairs,
                     func_080D9B08(payload->second_display), 160);
        func_080E0608(&payload->vertical, payload->y,
                     (s16)(payload->y - 96), 96);
        func_080E0608(&payload->horizontal, 0, 96, 32);
        payload->counter = 64;
        payload->retained_task = func_080DFD8C(data_0839D758, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x102: {
        void *display_data;
        u32 mask;
        if (payload->counter != 0) {
            if (--payload->counter == 0) {
                payload->effect_task = func_080DCFE4(payload->actor_state,
                                                    data_0839D744, 12, 0,
                                                    12, task, 0);
                payload->second_task = func_080D4704(data_089492DC, task);
            }
        } else {
            func_080E064C(&payload->horizontal);
            display_data = func_080D9B08(payload->second_display);
            func_0814186C(payload->pairs + payload->horizontal.current,
                         display_data,
                         (160 - payload->horizontal.current) & 0x1fffff);
            func_080D9B98(payload->second_display);
        }
        func_080E064C(&payload->vertical);
        func_080D7468(data_088F5ADC, 2, payload->x, payload->vertical.current);
        if (func_080E0690(&payload->vertical) == 0)
            break;
        if (func_080E0690(&payload->horizontal) == 0)
            break;
        func_080D9ADC(payload->second_display, 0, 16);
        mask = func_080035A8(2);
        g_control_flags_03000940 &= ~mask;
        descriptor->phase++;
        break;
    }
    case 0x103:
        payload->second_task = func_080D4774(payload->second_task);
        if (payload->second_task != 0)
            break;
        payload->actor_task = func_080FDEBC(payload->actor_task);
        if (payload->actor_task != 0)
            break;
        payload->first_task = func_080D3F08(payload->first_task);
        if (payload->first_task != 0)
            break;
        payload->first_display = func_080D9B64(payload->first_display);
        if (payload->first_display != 0)
            break;
        payload->second_display = func_080D9B64(payload->second_display);
        if (payload->second_display != 0)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
