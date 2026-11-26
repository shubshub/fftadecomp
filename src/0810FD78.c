#include "ffta.h"
#include "control_flags.h"

/* Target 0x0810FD78..0x081101DA, 1122 bytes including literal pools.  Task
 * callback: a sprite drops in from above the screen while the window that
 * shows BG2 narrows to nothing, bobs through the step tables at
 * 0x083A2EC4/0x083A2ECB, then moves down off the screen and back up to
 * y = -8 and is released.  Progress is reported through the status byte the
 * descriptor points at.
 */

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    u8 *status;
} Descriptor;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u16 counter;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    s32 y_fixed;
    u32 velocity;
    u8 *status;
    void *sprite;
    void *blend_task;
    void *layer_task;
    void *second_layer_task;
    InterpolationState window;
    InterpolationState drop;
    void *record_task;
    void *second_record_task;
} Payload;

extern const u8 data_088F46CC[];
extern const u8 data_083A2ED2[];
extern const u8 data_083A2EE8[];
extern const u8 data_083A2EF0[];
extern const u8 data_083A2ECB[];
extern const s8 data_083A2EC4[];
extern const u8 data_0894A8A4[];
extern const u8 data_0894A8E4[];
extern const u8 data_08501D1C[];
extern u16 data_03003920[];
extern u16 data_03003B20[];

extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void func_0814186C(const void *, void *, u32);
extern u32 func_080035D0(u8);
extern u32 func_080035A8(u8);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u8);
extern void func_0801121C(void *, s16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void func_080107D4(void *, s16, s16, u8);
extern void func_08011428(void *);

u32 func_0810FD78(void *task, Descriptor *descriptor, Payload *payload)
{
    u8 i;

    switch (descriptor->phase) {
    case 0:
        payload->status = descriptor->status;
        *payload->status = 0;
        payload->blend_task = func_080D3E9C(data_083A2ED2, task);
        g_control_flags_03000940.win0h_hi = 0x44;
        g_control_flags_03000940.win0h_lo = 0xAC;
        {
            /* CpuFill16: one halfword source for all 16 transfers. */
            volatile u16 fill = 0x7FFF;
            func_0814186C((const void *)&fill, data_03003920, 0x01000010);
        }
        g_control_flags_03000940.winin_lo = 0x3F;
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xFF;
        g_control_flags_03000940.display |= 0x2000;
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        payload->record_task = func_080DFD8C(data_083A2EE8, 1, 4, 0, task);
        break;
    case 1:
        /* The switch tests phase 1 on its own at 0x0810FD96..0x0810FD9A. */
        break;
    case 0x100:
        payload->blend_task = func_080D3F08(payload->blend_task);
        if (payload->blend_task)
            break;
        {
            volatile u16 fill = 0x7FFF;
            func_0814186C((const void *)&fill, data_03003B20, 0x01000010);
        }
        payload->x = 120;
        payload->y = -8;
        payload->y_fixed = payload->y << 16;
        payload->velocity = 0x2E666;
        payload->sprite = func_080D5CC0(data_08501D1C, 0, 120, payload->y,
                                        0x398, 6, 0, 0);
        func_0801121C(payload->sprite, -1);
        payload->counter = 20;
        descriptor->phase++;
        break;
    case 0x101:
        if (payload->counter != 0) {
            if (--payload->counter == 0) {
                payload->layer_task = func_080D4704(data_0894A8A4, task);
                func_080E0608(&payload->window, 0x34, 0, 0x3C);
                payload->second_record_task =
                    func_080DFD8C(data_083A2EF0, 1, 4, 0, task);
            }
        } else {
            if (!func_080E0690(&payload->window)) {
                func_080E064C(&payload->window);
                g_control_flags_03000940.win0h_hi = 0x78 - payload->window.current;
                g_control_flags_03000940.win0h_lo = payload->window.current + 0x78;
                if (func_080E0690(&payload->window)) {
                    /* The zero source at sp+0x14 (address formed at
                     * 0x0810FF8A) compiles the same with or without the
                     * SDK's volatile, unlike the two 0x7FFF fills above. */
                    u16 fill = 0;

                    func_0814186C(&fill, data_03003920, 0x01000010);
                    g_control_flags_03000940.bldcnt_lo = 0;
                    g_control_flags_03000940.display &= ~0x2000;
                    g_control_flags_03000940.display &= ~func_080035A8(2);
                    payload->second_layer_task =
                        func_080D4704(data_0894A8E4, task);
                }
            }
        }
        payload->y_fixed += payload->velocity;
        payload->velocity -= 0x7AE;
        if (payload->velocity < 0x1999)
            payload->velocity = 0x1999;
        payload->y = payload->y_fixed >> 16;
        if (payload->y > 0x87) {
            payload->y = 0x88;
            *payload->status = 1;
            descriptor->phase++;
        }
        func_080107D4(payload->sprite, payload->x, payload->y, 0);
        payload->layer_task = func_080D4774(payload->layer_task);
        break;
    case 0x102:
        for (i = 0; i < 7; i++) {
            if (payload->counter == data_083A2ECB[i]) {
                if (data_083A2EC4[i] == 0) {
                    payload->counter = 0;
                    i = 0;
                }
                payload->y += data_083A2EC4[i];
                break;
            }
        }
        payload->counter++;
        func_080107D4(payload->sprite, payload->x, payload->y, 0);
        if (*payload->status != 2)
            break;
        payload->second_layer_task = func_080D4774(payload->second_layer_task);
        if (payload->second_layer_task)
            break;
        descriptor->phase++;
        break;
    case 0x103:
        for (i = 0; i < 7; i++) {
            if (payload->counter == data_083A2ECB[i]) {
                if (data_083A2EC4[i] == 0) {
                    payload->counter = 0;
                    i = 0;
                }
                payload->y += data_083A2EC4[i];
                break;
            }
        }
        payload->counter++;
        func_080107D4(payload->sprite, payload->x, payload->y, 0);
        if (*payload->status == 3) {
            func_080E0608(&payload->drop, payload->y, 0x100, 0xB4);
            payload->counter = 0;
            descriptor->phase++;
        }
        break;
    case 0x104:
        func_080E064C(&payload->drop);
        payload->y = payload->drop.current;
        func_080107D4(payload->sprite, payload->x, payload->y, 0);
        if (++payload->counter == 0xAA)
            *payload->status = 4;
        if (func_080E0690(&payload->drop)) {
            func_080E0608(&payload->drop, payload->y, -8, 0x14);
            descriptor->phase++;
        }
        break;
    case 0x105:
        func_080E064C(&payload->drop);
        payload->y = payload->drop.current;
        func_080107D4(payload->sprite, payload->x, payload->y, 0);
        if (++payload->counter == 0xB8)
            *payload->status = 5;
        if (func_080E0690(&payload->drop)) {
            func_08011428(payload->sprite);
            payload->sprite = 0;
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
