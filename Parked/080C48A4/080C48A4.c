#include "ffta.h"

typedef struct ActionState {
    void *source;
    void *target;
    u8 unknown_08[0x1E];
    u16 flags;
} ActionState;

extern ActionState data_0200F3F0;
extern s32 func_0812F0D8(const void *unit, u16 *entries);
extern u8 func_080C8280(const void *unit);
extern u32 func_080CCD50(u16 action, u8 attribute);
extern void func_0812F2A4(u16 action, u16 equipment, u8 kind);
extern void func_0812F328(u8 index);
extern void func_0812F34C(u32 value);
extern void func_0812F39C(s32 index);
extern u8 func_08130FBC(void);
extern u8 func_08131378(void);

u8 func_080C48A4(void *source, void *target, u16 action)
{
    ActionState *state;
    u16 entries[2];
    u16 equipment;
    s32 index;

    if ((s16)func_0812F0D8(source, entries) == 0)
        entries[0] = 0;
    equipment = entries[0];
    state = &data_0200F3F0;
    if (action == 0) {
        if (source == target)
            return 0;
        return !func_080C8280(target);
    }
    if (func_080CCD50(action, 11) == 0 && source == target)
        return 0;

    func_0812F2A4(action, equipment, 0);
    state->source = source;
    state->target = target;
    state->flags |= 0x10;
    for (index = 0; index < 3; ++index) {
        func_0812F328(index);
        func_0812F34C(0);
        if (func_08130FBC() && func_08131378()) {
            func_0812F39C(index);
            func_0812F34C((u32)target);
            return 1;
        }
    }
    return 0;
}
