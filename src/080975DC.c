#include "ffta.h"

typedef struct {
    void *record;
    u8 unknown_04[0x1B];
    u8 direction;
    u8 alternate_direction;
    u8 unknown_21[0x0F];
    u32 flags;
    u16 sprite;
    u16 requested_animation;
    u8 unknown_38[8];
    void *context;
    void *display;
    void *extra;
} AnimationState;

extern u16 func_08021054(u32 index);
extern u8 func_080CDCD4(const void *record);
extern u32 func_080C92F0(void *record, u32 selector);
extern void *func_08021618(void *context, void *display, u32 kind,
                          u32 resource, u32 sprite, s32 animation, u32 variant);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern void func_08021D98(u32 *context, u32 value);
extern void *func_08021B9C(void *context);
extern void func_08021C84(void *state, u16 first, s32 second);
extern void func_08021C38(void *state, u8 value);
extern void func_08021C08(u32 *state, u8 enabled);

static inline u8 offset_locked(void *owner)
{
    switch (func_080C92F0(owner, 0x28) & 2) {
    case 0:
        break;
    default:
        return 1;
    }
    return 0;
}

/* Complete [0x080975DC, 0x08097704): 296 bytes. */
void func_080975DC(AnimationState *state, u16 animation, u8 direction, s32 automatic)
{
    u16 resource = func_08021054(state->sprite);

    state->requested_animation = animation;
    if (automatic && animation == 0) {
        if (state->flags & 8)
            animation = 12;
        if (state->flags & 16) {
            if (func_080CDCD4(state->record))
                animation = 12;
            else
                animation = 20;
        }
        if (state->flags & 0x800) {
            if (state->flags & 0x20)
                animation = 12;
            else
                animation = 128;
        }
        if (state->flags & 0x400)
            animation = 140;
    }
    state->direction = direction;
    if (offset_locked(state->record))
        direction = state->alternate_direction;
    state->display = func_08021618(state->context, state->display, 0,
                                  resource, state->sprite, animation + (s8)direction, 0);
    if (automatic && animation == 0) {
        if (state->flags & 0x100)
            func_0809A570(state, 0, 0x1000);
        else if (state->flags & 0x200)
            func_0809A570(state, 0, 0x4000);
    }
    func_08021D98(state->context, (u32)state->display);
    if (state->extra == 0) {
        state->extra = func_08021B9C(state->context);
        func_08021C84(state->extra, 0x147, 0);
        func_08021C38(state->extra, 2);
        func_08021C08(state->extra, 1);
    }
}
