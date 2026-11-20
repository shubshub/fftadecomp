#include "control_flags.h"

struct Descriptor {
    u16 phase;
    u16 unknown_02;
    void *resource;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u16 counter;
    u16 unknown_02;
    u32 unknown_04;
    void *resource;
    void *pieces[10];
    void *shards[16];
    struct InterpolationState piece_x[10];
    struct InterpolationState piece_y[10];
    u8 unknown_164[0xF0];
    u16 angles[10];
    struct InterpolationState shard_x[16];
    struct InterpolationState shard_y[16];
    struct InterpolationState window_size;
    void *task;
    void *window;
    void *sequence;
};

struct PieceDefinition {
    s16 x;
    s16 y;
    s16 end_x;
    s16 end_y;
    const s16 *scale_x;
    const s16 *scale_y;
    s16 spin;
    u16 unknown_12;
};

struct ShardDefinition {
    s16 x;
    s16 y;
    s16 end_x;
    s16 end_y;
};

/* Not const: the ROM reloads x and y from the entry after each call
 * (0x08111708, 0x0811171A, 0x08111772, 0x08111788), which agbcc does not
 * do for a const table. */
extern struct PieceDefinition data_083A3264[];
extern struct ShardDefinition data_083A332C[];
extern const u8 data_08504E58[];
extern const u8 data_08504EFC[];
extern const u8 data_0894BD50[];
extern const u8 data_0894BD40[];
extern const u8 data_083A33BC[];

extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_080110F8(void *, u8);
extern void func_080112E8(void *, u8);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_080107D4(void *, s16, s16, u8);
extern void func_080112CC(void *, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void func_080D5F74(void **, u16);
extern u16 func_080035D0(u8);
extern u16 func_080035A8(u8);
extern void *func_080DAB84(u8, u8, u8, void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080DAC40(void *, u16, u16, u16);
extern void *func_080D9B64(void *);

/* Complete target: [0x0811166C, 0x08111A5C), 1008 bytes. */
u32 func_0811166C(void *task, struct Descriptor *descriptor, struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->resource = descriptor->resource;
        break;
    case 0x100: {
        u8 index;

        for (index = 0; index < 10; index++) {
            payload->pieces[index] = func_080D5CC0(data_08504E58, index,
                data_083A3264[index].x, data_083A3264[index].y, 0x33F, 7, 0, 0);
            func_080110F8(payload->pieces[index], 1);
            func_080112E8(payload->pieces[index], 1);
            func_080E0608(&payload->piece_x[index], data_083A3264[index].x,
                          data_083A3264[index].end_x, 60);
            func_080E0608(&payload->piece_y[index], data_083A3264[index].y,
                          data_083A3264[index].end_y, 60);
        }
        for (index = 0; index < 16; index++) {
            payload->shards[index] = func_080D5CC0(data_08504EFC, index,
                data_083A332C[index].x, data_083A332C[index].y, 0x32C, 7, 0, 0);
            func_080E0608(&payload->shard_x[index], data_083A332C[index].x,
                          data_083A332C[index].end_x, 60);
            func_080E0608(&payload->shard_y[index], data_083A332C[index].y,
                          data_083A332C[index].end_y, 60);
        }
        payload->task = func_080D4704(data_0894BD50, task);
        descriptor->phase++;
        break;
    }
    case 0x101: {
        u8 index;
        /* Full-width: each scale is sign-extended where it is loaded
         * (ldrsh at 0x0811181A, 0x0811183A) and passed unnarrowed
         * (0x0811187C, 0x0811187E). */
        int scale_x;
        int scale_y;
        u16 angle;

        for (index = 0; index < 10; index++) {
            angle = 0;
            func_080E064C(&payload->piece_x[index]);
            func_080E064C(&payload->piece_y[index]);
            scale_x = 0x100;
            if (data_083A3264[index].scale_x != 0)
                scale_x = data_083A3264[index].scale_x[payload->counter];
            scale_y = 0x100;
            if (data_083A3264[index].scale_y != 0)
                scale_y = data_083A3264[index].scale_y[payload->counter];
            if (data_083A3264[index].spin != 0) {
                payload->angles[index] += data_083A3264[index].spin;
                angle = payload->angles[index];
            }
            func_080107D4(payload->pieces[index], payload->piece_x[index].current,
                          payload->piece_y[index].current, 0);
            func_080112CC(payload->pieces[index], scale_x, scale_y, angle);
        }
        for (index = 0; index < 16; index++) {
            func_080E064C(&payload->shard_x[index]);
            func_080E064C(&payload->shard_y[index]);
            func_080107D4(payload->shards[index], payload->shard_x[index].current,
                          payload->shard_y[index].current, 0);
        }
        payload->counter++;
        payload->task = func_080D4774(payload->task);
        if (payload->task == 0) {
            func_080D5F74(payload->pieces, 10);
            func_080D5F74(payload->shards, 16);
            g_control_flags_03000940.winin_lo = 0x3f & ~func_080035D0(3);
            g_control_flags_03000940.winout_lo = 0x3f;
            g_control_flags_03000940.win0h_hi = 0;
            g_control_flags_03000940.win0h_lo = 0;
            g_control_flags_03000940.win0v_hi = 0;
            g_control_flags_03000940.win0v_lo = 0xff;
            g_control_flags_03000940.display |= 0x2000;
            func_080E0608(&payload->window_size, 0, 150, 16);
            payload->window = func_080DAB84(0, 0, 0, task);
            func_080D9BA8(payload->window, 1);
            payload->sequence = func_080DFD8C(data_083A33BC, 1, 4, 0, task);
            payload->counter = 20;
            descriptor->phase++;
        }
        break;
    }
    case 0x102:
        if (payload->counter != 0) {
            if (--payload->counter != 0)
                break;
            payload->task = func_080D4704(data_0894BD40, task);
        }
        if (!func_080E0690(&payload->window_size)) {
            func_080E064C(&payload->window_size);
            func_080DAC40(payload->window, 120, 80, payload->window_size.current);
            if (func_080E0690(&payload->window_size)) {
                g_control_flags_03000940.display &= ~func_080035A8(3);
                g_control_flags_03000940.display &= ~0x2000;
            }
        } else if (!(payload->window = func_080D9B64(payload->window)) &&
                   !(payload->task = func_080D4774(payload->task))) {
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
