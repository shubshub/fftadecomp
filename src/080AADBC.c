#include "ffta.h"

/* Complete [0x080AADBC, 0x080AB356): 1434 bytes, with literal pools at
 * 0x080AB004, 0x080AB148, 0x080AB2B0 and 0x080AB30C. */

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x11];
    s8 direction;
    u8 unknown_20[0x10];
    u32 flags;
} Actor;

typedef struct {
    s32 velocity;
    s32 height;
    s32 destination;
} Motion;

/* A sprite definition is a count followed by packed six-byte OAM entries
 * (src/08021064.c reads the same layout); the template copied below,
 * data_08394568, is one entry.  The packing is why the ROM writes the
 * 10-bit tile number a byte at a time (0x080AB128-0x080AB138). */
typedef struct __attribute__((packed)) {
    u16 attr0;
    u16 attr1;
    u16 tile : 10;
    u16 priority : 2;
    u16 palette : 4;
} SpriteOam;

typedef struct __attribute__((packed)) {
    u16 count;
    SpriteOam oam[1];
} Sprite;

/* One of the two pieces thrown up on landing; func_080A9B00 reads its
 * fields from 0x2E on (src/080A9B00.c). */
typedef struct {
    const Sprite *sprite;
    Motion motion;
    u8 unknown_10[0x1E];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_34[4];
    u16 unknown_38;
    u16 unknown_3A;
    u16 unknown_3C;
    u8 unknown_3E[0x1A];
} Debris;

typedef struct {
    Actor *actor;
    Motion motion;
    u8 unknown_10[0x26];
    u16 animation;
    u8 unknown_38[6];
    s8 direction;
    u8 unknown_3F;
    u8 flags;
    u8 unknown_41;
    u16 tile_base;
    Debris debris[2];
    s16 effect_x;
    s16 effect_y;
    s16 effect_z;
    u8 unknown_FA[2];
    u8 effect_flag;
    u8 effect_flag2;
    u8 unknown_FE[0x14];
    Sprite sprite;
    u8 unknown_11A[0x18];
    s8 step_x;
    s8 step_z;
    s8 debris_step_x;
    s8 debris_step_z;
    s16 destination_x;
    s16 destination_z;
    u16 unknown_13A;
    u16 phase;
    u8 unknown_13E[0x4A];
    u8 mode;
} State;

typedef void (*BufferCopier080AADBC)(void *destination, const void *source,
                                    u32 size);

extern BufferCopier080AADBC const data_0836D4BC[];
extern const Sprite data_08394568;

extern void func_080A9B00(Debris *debris);
extern void func_0809D66C(s8 direction, s8 *x, s8 *z);
extern void func_0809836C(Actor *actor, u16 animation, s8 direction, u16 command);
extern s32 func_08099C34(Actor *actor);
extern u32 func_08099C64(const Actor *actor);
extern void func_08141520(u16 sound);
extern void func_08141570(s32 player, u16 song);
extern void func_080A92E4(u16 mode, s16 x, s16 y, s16 z, u32 effect);
extern void func_080A7EC4(u16 command);
extern void func_0809A570(Actor *actor, u32 clear, u32 set);
extern void func_080A8390(s8 first, s8 second, s8 *left, s8 *right);
extern u32 func_08002804(void);
extern int abs(int value);
extern void func_080E2C00(const void *effect, s16 x, s16 y, s16 z, u8 argument, u8 status);
extern u8 func_080A9E6C(State *state, s32 distance);

/* One step of the bounce under gravity 0x99, used for the two pieces
 * (0x080AAE02-0x080AAE18) and for the actor in phases 1 and 2
 * (0x080AB23A-0x080AB258, 0x080AB2E6-0x080AB304).  The velocity is read
 * through the owner and the height and floor through the motion pointer
 * m.  Phase 1 shows the split: it loads the velocity through state
 * (0x080AB23E, and again at 0x080AB244 after the height store) and the
 * height and floor through the motion pointer in r8 (0x080AB23C,
 * 0x080AB24C).  The piece loop addresses all three through the piece (r7,
 * offsets 4, 8 and 0xC at 0x080AAE02-0x080AAE18), and in phase 2, as in
 * the siblings src/080A9F24.c and src/080ABBD8.c, the two spellings
 * compile alike. */
#define FALL(owner, m, moving)                                          \
    {                                                                   \
        (m)->height += (owner)->motion.velocity;                        \
        (owner)->motion.velocity -= 0x99;                               \
        if ((m)->destination >= (m)->height                             \
            && (owner)->motion.velocity <= 0) {                         \
            (m)->height = (m)->destination;                             \
            (moving) = 0;                                               \
        } else {                                                        \
            (moving) = 1;                                               \
        }                                                               \
    }

u32 func_080AADBC(State *state, Actor *target, u32 unused, const void *effect)
{
    s32 i;
    s32 busy;
    s8 left;
    s8 right;
    u8 moving;

    if (state->flags & 8) {
        busy = 0;
        for (i = 0; i < 2; i++) {
            Motion *motion = &state->debris[i].motion;
            s32 height = state->debris[i].motion.height;

            func_080A9B00(&state->debris[i]);
            FALL(&state->debris[i], motion, moving);
            if (moving)
                busy = 1;
            else if (height != state->debris[i].motion.height) {
                if (state->mode == 0) {
                    if (i != 0) {
                        func_080A92E4(0, target->x, target->y, target->z, 0x15);
                        func_08141570(2, 0x8D);
                    }
                } else {
                    func_080A7EC4(state->animation);
                    func_0809836C(target, 5, target->direction, 0);
                    func_0809A570(target, 0, 0x8000);
                    func_080A8390(state->actor->direction, target->direction, &left, &right);
                    if (left)
                        func_0809A570(target, 0, 0x200);
                    if (right)
                        func_0809A570(target, 0, 0x400);
                    state->effect_x = (s16)func_08002804() % 17 + target->x - 16;
                    state->effect_y = (s16)((s16)func_08002804() % 17 + 4) + target->y;
                    state->effect_z = (s16)func_08002804() % 17 + target->z - 16;
                    state->effect_flag = 0;
                    state->effect_flag2 = 0;
                    func_080E2C00(effect, state->effect_x, state->effect_y, state->effect_z,
                                  state->effect_flag, state->effect_flag2);
                }
            }
            if (state->debris[i].motion.velocity > 0) {
                /* Cases 2 and default cannot be reached with two pieces;
                 * the ROM keeps both (0x080AAF7E, 0x080AAF8C).  Case 1's
                 * x++ (0x080AAF78, stored at 0x080AAF88) is overwritten by
                 * the x store below (0x080AAFAA), so it has no effect. */
                switch (i) {
                case 0:
                    state->debris[i].y++;
                    break;
                case 1:
                    state->debris[i].x++;
                    break;
                case 2:
                    state->debris[i].z++;
                    break;
                default:
                    state->debris[i].y--;
                    break;
                }
            }
            state->debris[i].x = state->debris_step_x * (state->debris[i].motion.height >> 8) + target->x;
            state->debris[i].z = state->debris_step_z * (state->debris[i].motion.height >> 8) + target->z;
        }
        if (!busy)
            state->flags &= ~0xC;
    }

    switch (state->phase) {
    case 0: {
        SpriteOam *oam;

        state->flags |= 2;
        state->actor->flags &= ~1;
        func_0809D66C(state->direction, &state->step_x, &state->step_z);
        state->actor->x = (((target->x >> 5) - state->step_x) << 5) + 16;
        state->actor->z = (((target->z >> 5) - state->step_z) << 5) + 16;
        state->destination_x = (((target->x >> 5) - state->step_x * 4) << 5) + 16;
        state->destination_z = (((target->z >> 5) - state->step_z * 4) << 5) + 16;
        state->step_x *= -1;
        state->step_z *= -1;
        state->motion.destination = target->y << 8;
        state->motion.height = (target->y - 0x30) << 8;
        state->motion.velocity = 0x800;
        state->actor->y = state->motion.height >> 8;
        func_0809836C(state->actor, 7, state->direction, state->animation);
        data_0836D4BC[0](&state->sprite, &data_08394568, sizeof(state->sprite));
        /* The ROM forms the entry's address before the loop
         * (0x080AB0F2) and patches its tile after it. */
        oam = state->sprite.oam;
        for (i = 0; i < 2; i++) {
            state->debris[i].sprite = &state->sprite;
            state->debris[i].unknown_3A = 0;
            state->debris[i].unknown_3C = 0;
            state->debris[i].unknown_38 = 0;
        }
        oam->tile = state->actor->direction * 4 + state->tile_base;
        state->phase = 1;
        break;
    }
    case 1: {
        s32 event = func_08099C34(state->actor);
        Motion *motion = &state->motion;

        if (event == 0) {
            func_08141520(0x7F);
            state->flags |= 0xC;
            for (i = 0; i < 2; i++) {
                state->debris[i].x = state->actor->x;
                state->debris[i].y = state->actor->y + 0x18;
                state->debris[i].z = state->actor->z;
                state->debris[i].motion.destination = 0;
                state->debris[i].motion.velocity =
                    (((s16)((s16)func_08002804() % 7) + 3) * i + 3) << 8;
                if (state->step_x)
                    state->debris[i].motion.height = abs(target->x - state->actor->x) << 8;
                else
                    state->debris[i].motion.height = abs(target->z - state->actor->z) << 8;
            }
            state->debris_step_x = state->step_x;
            state->debris_step_z = state->step_z;
        }
        FALL(state, motion, moving);
        state->actor->y = state->motion.height >> 8;
        func_080A9E6C(state, 4);
        if (func_08099C64(state->actor)) {
            func_0809836C(state->actor, 3, state->direction, 0);
            state->motion.destination = (target->y - 0x30) << 8;
            state->motion.height = target->y << 8;
            state->motion.velocity = 0;
            state->actor->y = state->motion.height >> 8;
            state->phase = 2;
        }
        break;
    }
    case 2: {
        Motion *motion;

        if (state->step_x)
            state->actor->x += state->step_x * 4;
        if (state->step_z)
            state->actor->z += state->step_z * 4;
        motion = &state->motion;
        FALL(state, motion, moving);
        state->actor->y = state->motion.height >> 8;
        if (!moving) {
            state->actor->flags |= 1;
            state->flags &= ~2;
            if (!(state->flags & 0xC)) {
                state->flags = 0;
                return 0;
            }
        }
        break;
    }
    }
    return 1;
}
