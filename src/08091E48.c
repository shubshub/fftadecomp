#include "ffta.h"
#include "control_flags.h"

/* Complete [0x08091E48, 0x08092082): 570 bytes, including the eleven-entry
 * jump table at 0x08091ECC and the literal pools.  Advances and draws the
 * object's animation while it is visible, then steps the eleven-phase
 * sequence kept at +0x64. */

/* The animation state func_080A8DB8 advances (src/080A8DB8.c) and
 * func_080A8E0C draws (src/080A8E0C.c); only the members read here. */
typedef struct {
    u8 unknown_00[8];
    s16 number;
    u8 unknown_0A[4];
    s16 index;
    u8 unknown_10[4];
    const u8 *current;
    const u8 *script;
    u8 unknown_1c;
    u8 unknown_1D[9];
    s16 x;
    s16 y;
} AnimationState;

typedef struct {
    AnimationState animation;
    s16 x;
    s16 y;
    u8 unknown_30[0x28];
    void *allocation;
    u8 visible;
    u8 variant;
    u8 step;
    u8 timer;
    void *task;
    u16 phase;
} Object08091E48;

typedef struct {
    u8 unknown_00[0x16];
    u16 filtered_pressed;
} InputState;

/* Seventeen BLDALPHA coefficient pairs, (16, 0) down to (0, 16). */
typedef struct {
    u8 eva;
    u8 evb;
    u8 unknown_02[2];
} BlendStep;

extern InputState g_state_0200F390;
extern const BlendStep data_0839430C[];

/* The definition (src/080A946C.c) forwards r0 to func_080A8DB8 unnamed;
 * the state is loaded for it at 0x08091E68. */
extern void func_080A946C(AnimationState *state);
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);
extern void func_08022854(u8 *object);
extern void func_08141748(u16 interval);
extern void func_08141520(u16 value);
extern void func_080D376C(void);
extern void func_080D3A50(u8 disabled);
extern u8 func_080D37F8(void);
extern u8 func_080D39B0(void);
extern void *func_080D3508(u16 id, void *object, u32 arg);
extern u8 func_080D3878(const void *object);
extern void func_080D3A88(u8 enabled);
extern void func_080D37AC(void);
extern u8 func_080D37C4(void);

/* The text of read_le16_0801075C (src/0801075C.c): the script's first two
 * bytes are its frame count, low byte first (0x08091E58, 0x08091F3E). */
static inline u16 read_le16(const u8 *data)
{
    u32 low = data[0];

    return (data[1] << 8) | low;
}

/* Draws the current frame at a position relative to the animation's own.
 * The three arguments are computed at 0x08091E6E-0x08091E80, before the
 * frame is tested at 0x08091E82-0x08091E86. */
static inline void draw_animation(AnimationState *state, s32 x, s32 y,
                                  u32 variant)
{
    if (state->current)
        func_08001F34(state->current, x + state->x, y + state->y, variant,
                      0, 0, 0, 0, state->number, 0,
                      (const void *)(u32)state->unknown_1c);
}

u8 func_08091E48(Object08091E48 *object)
{
    if (object->visible) {
        if (read_le16(object->animation.script) > object->animation.index)
            func_080A946C(&object->animation);
        draw_animation(&object->animation, object->x + 0x78, object->y + 0x50,
                       object->variant);
    }

    switch (object->phase) {
    case 0:
        func_08022854(object->allocation);
        func_08141748(4);
        object->timer = 100;
        object->phase = 1;
        break;
    case 1:
        if (--object->timer == 0) {
            func_08141520(7);
            object->allocation = 0;
            object->visible = 1;
            object->phase = 2;
        }
        break;
    case 2:
        if (read_le16(object->animation.script) <= object->animation.index) {
            func_080D376C();
            func_080D3A50(0);
            object->phase = 3;
        }
        break;
    case 3:
        if (func_080D37F8() && func_080D39B0()) {
            object->task = func_080D3508(0x15E, 0, 0);
            object->phase = 4;
        }
        break;
    case 4:
        if (func_080D3878(object->task))
            object->phase = 5;
        break;
    case 5:
        func_080D3A88(0);
        func_080D37AC();
        object->phase = 6;
        break;
    case 6:
        if (func_080D37C4())
            object->phase = 7;
        break;
    case 7:
        if (g_state_0200F390.filtered_pressed & 0x30F)
            object->phase = 8;
        break;
    case 8:
        object->variant = 1;
        g_control_flags_03000940.bldcnt_lo = 0x40;
        g_control_flags_03000940.bldcnt_hi = 0x3F;
        g_control_flags_03000940.bldalpha_lo = 0x10;
        g_control_flags_03000940.bldalpha_hi = 0;
        object->step = 0;
        object->timer = 0;
        object->phase = 9;
        break;
    case 9:
        g_control_flags_03000940.bldalpha_lo = data_0839430C[object->step].eva;
        g_control_flags_03000940.bldalpha_hi = data_0839430C[object->step].evb;
        if (++object->timer > 3) {
            object->timer = 0;
            object->step++;
            if (object->step > 0x10)
                object->phase = 10;
        }
        break;
    case 10:
        return 0;
    }
    return 1;
}
