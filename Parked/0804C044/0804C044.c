#include "ffta.h"

/* Complete [0x0804C044, 0x0804C4D4): 1168 bytes, 488 instructions.
 *
 * Per-frame task callback (installed by func_08035174).  It draws every
 * active 28-byte record of the list at data_03000E30 and steps its
 * animation, then, on task state 0, slides two gauge sprites and draws two
 * fixed sprites, and finally draws the menu cursor at the selected position
 * of the menu state, bobbing it through data_08393CA2 (48 phases) or
 * data_08393D02 (40 phases).
 */

typedef struct {
    u16 cell;
    u16 duration;
} AnimFrame;

typedef struct {
    AnimFrame *frames;   /* +0x00 */
    u8 *source;          /* +0x04 */
    u16 frame;           /* +0x08 */
    u16 mode;            /* +0x0A */
    u8 type;             /* +0x0C */
    u8 active;           /* +0x0D */
    u8 count;            /* +0x0E */
    u8 timer;            /* +0x0F */
    u8 x;                /* +0x10 */
    u8 y;                /* +0x11 */
    u8 field_12;         /* +0x12 */
    u8 field_13;         /* +0x13 */
    u8 field_14;         /* +0x14 */
    u8 unknown_15;
    u16 field_16;        /* +0x16 */
    u8 *base;            /* +0x18 */
} AnimEntry;             /* 28 bytes */

typedef struct {
    u16 count;
    u16 unknown_02;
    void *entries;
} AnimList;

typedef struct {
    u8 flags;
    u8 unknown_01[0x17];
    u8 field_18;
    s8 field_19;
} Gauge;

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[2];
} CursorPosition;

typedef struct {
    u32 unknown_000;
    Gauge *gauge;                    /* +0x004 */
    u8 unknown_008[0xED4];
    CursorPosition positions[16];    /* +0xEDC */
    u8 count;                        /* +0xF1C */
    u8 state;                        /* +0xF1D */
    u8 unknown_F1E;
    u8 selection;                    /* +0xF1F */
    u8 previous_selection;           /* +0xF20 */
    u8 flags;                        /* +0xF21 */
} MenuState;

typedef struct {
    u8 unknown_00[0x34];
    s8 x;
    s8 y;
    u8 unknown_36[0x16];
} RenderRecord;

extern AnimList data_03000E30;
extern MenuState *g_state_03002810;
extern RenderRecord data_030009E0[];
extern const u8 data_083919B0[];
extern const u8 data_083919BE[];
extern const u8 data_083919C6[];
extern const u8 data_083919CE[];
extern const s8 data_08393CA2[];
extern const s8 data_08393D02[];

extern void func_08001CF0(const void *source, s32 x, s32 y, u8 mode,
                          u8 first_flag, u8 second_flag, u8 third_flag,
                          u8 fourth_flag, u32 value, u8 count, u32 extra);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, u32 transform);

void func_0804C044(void *task, u8 *state)
{
    AnimEntry *e = data_03000E30.entries;
    u16 i;
    u8 *gfx;

    for (i = 0; i < data_03000E30.count; i++, e++) {
        if (!e->active)
            continue;
        switch (e->type) {
        case 0:
        case 1:
            gfx = e->base + *(u32 *)(e->base + (e->frames[e->frame].cell << 2));
            if (e->type == 1)
                func_08001CF0(gfx, e->x, e->y, 0, 0, 0, 0, 0, e->field_16,
                              e->field_13, 0);
            else
                func_08001F34(gfx, e->x, e->y, 0, 0, 0, 0, 0, e->field_16,
                              e->field_13, e->field_12);
            if (++e->timer >= e->frames[e->frame].duration) {
                e->timer = 0;
                if (e->mode == 1)
                    e->frame = (e->frame + 1) % e->count;
                else if (e->frame + 1 < e->count)
                    e->frame++;
            }
            break;
        case 2: {
            u16 sprite[4];

            /* One OAM entry: count, attribute 0, attribute 1, tile. */
            sprite[0] = 1;
            sprite[1] = 0;
            sprite[2] = 0;
            sprite[3] = e->frame;
            func_08001F34(sprite, e->x, e->y, e->field_14, 0, 0, 0, 0, 0,
                          e->field_13, e->field_12);
            break;
        }
        case 3:
            func_08001F34(e->source, e->x, e->y, 0, 0, 0, 0, 0, 0,
                          e->field_13, e->field_12);
            break;
        case 4:
            func_08001CF0(e->source, e->x, e->y, 0, 0, 0, 0, 0, 0,
                          e->field_13, e->field_12);
            break;
        case 6:
            gfx = e->base + *(u32 *)(e->base + (e->frames[e->frame].cell << 2));
            func_08001F34(gfx, e->x, e->y, 0, 0, 0, 0, 0, e->field_16,
                          e->field_13, 0);
            break;
        case 5:
            func_08001F34(e->source + e->timer * 8, e->x, e->y, 0, 0, 0, 0, 0,
                          0, e->field_13, e->field_12);
            if (++e->mode >= e->frame) {
                e->mode = 0;
                if (++e->timer >= e->count)
                    e->timer = 0;
            }
            break;
        }
    }

    if (*state == 0) {
        func_0804C788(data_03000E30.entries, 2, 0xD4,
                      g_state_03002810->gauge->field_18);
        if (g_state_03002810->gauge->flags & 0x40) {
            if (g_state_03002810->gauge->field_19 < 24)
                g_state_03002810->gauge->field_19 += 2;
        } else {
            if (g_state_03002810->gauge->field_19 > 0)
                g_state_03002810->gauge->field_19 -= 2;
        }
        func_0804C788(data_03000E30.entries, 1, 4,
                      g_state_03002810->gauge->field_19);
        func_08001CF0(data_083919B0, 0x9C, data_030009E0[3].y * 8 + 1, 0,
                      0, 0, 0, 0, 0, 0, 0);
        func_08001CF0(data_083919BE, 0xE0, data_030009E0[3].y * 8 + 1, 0,
                      0, 0, 0, 0, 0, 0, 0);
    }

    if ((g_state_03002810->flags & 1) && !(g_state_03002810->flags & 0x10)) {
        s32 x, y;

        if (!(g_state_03002810->flags & 0x80)) {
            if (g_state_03002810->flags & 8)
                x = g_state_03002810->positions[g_state_03002810->selection].x
                    + data_08393CA2[g_state_03002810->state];
            else
                x = g_state_03002810->positions[g_state_03002810->selection].x
                    + 8 - data_08393CA2[g_state_03002810->state];
            y = g_state_03002810->positions[g_state_03002810->selection].y;
            func_08001CF0(data_083919C6, x, y, 0, 0, 0,
                          !(g_state_03002810->flags & 8), 0, 0, 0, 0);
            /* Both directions restart at phase 24: the ROM keeps the flag-8
             * test (0x0804C40C movs/ands/cmp, beq 0x0804C420) and each arm
             * forms the +0xF1D address (0x0804C414, 0x0804C420) before the
             * shared store of 24 at 0x0804C424. */
            if (g_state_03002810->flags & 2) {
                g_state_03002810->state++;
                g_state_03002810->state %= 48;
            } else if (g_state_03002810->flags & 8) {
                g_state_03002810->state = 24;
            } else {
                g_state_03002810->state = 24;
            }
        } else {
            x = g_state_03002810->positions[g_state_03002810->selection].x;
            y = g_state_03002810->positions[g_state_03002810->selection].y;
            func_08001F34(data_083919CE, x, y, 0, 0, 0, 0, 0,
                          data_08393D02[g_state_03002810->state], 0, 0);
            if (g_state_03002810->flags & 2) {
                g_state_03002810->state++;
                g_state_03002810->state %= 40;
            } else {
                g_state_03002810->state = 0;
            }
        }
    }
}
