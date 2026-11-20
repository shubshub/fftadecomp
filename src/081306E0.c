#include "ffta.h"

typedef struct ActionState {
    void *source;
    void *target;
    u8 unknown_08[0x1E];
    u16 flags;
} ActionState;

extern ActionState data_0200F3F0;
extern s32 func_0812F0D8(const void *source, u16 *equipment);
extern void func_0812F2A4(u16 action, u16 equipment, u8 kind);
extern void func_0812F328(u8 index);
extern void func_0812F34C(u32 value);
extern u8 func_0812F358(void);
extern void func_0812F39C(s32 index);
extern u8 func_08130FBC(void);
extern s32 func_08131B20(void);

/* Complete [0x081306E0, 0x0813079C), 188 bytes. */
u8 func_081306E0(void *source, void *target, u16 action)
{
    ActionState *state = &data_0200F3F0;
    u16 equipment[2];
    s32 index;

    func_0812F0D8(source, equipment);
    if (!action)
        return 1;

    func_0812F2A4(action, equipment[0], 0);
    state->source = source;
    state->target = target;
    state->flags |= 2;

    for (index = 0; index < 3; index++) {
        func_0812F328((u8)index);
        func_0812F34C(0);
        if (func_08130FBC()) {
            func_0812F39C(index);
            func_0812F34C((u32)target);
            switch (func_0812F358()) {
            case 1:
            case 5:
                return func_08131B20() > 0;
            case 2:
            case 3:
            case 4:
            case 6:
            case 7:
                return 0;
            case 8:
                return 1;
            }
        }
    }
    return 0;
}
