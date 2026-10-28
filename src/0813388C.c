#include "ffta.h"

typedef struct Unit Unit;

typedef struct {
    u8 unknown_00;
    u8 kind;
} ActionRecord;

typedef struct {
    Unit *source;
    u32 unknown_04;
    Unit *target;
    u16 action_id;
    u16 equipment_id;
    u8 unknown_10[0x10];
    s16 values[3];
    u16 flags;
    u8 selected;
    u8 unknown_29[7];
    ActionRecord *record;
} ActionState;

typedef struct {
    u32 value;
    u32 unknown_04;
    s8 mode;
    u8 unknown_09[3];
} ActionDescriptor;

extern ActionState data_0200F3F0;
extern const ActionDescriptor data_083A87B0[];
extern u8 func_08133A58(const Unit *unit, s32 kind);
extern void func_08142248(ActionState *state, u32 value);
extern u8 func_0812F358(void);
extern void func_08131C28(u32 selector, void *object);
extern void func_08130688(u16 equipment_id, u16 action_id, Unit *unit);
extern void func_08131C58(void *object);
extern void func_080CA2E8(void *object);

/* 0x0813388C..0x08133970: 228 bytes; apply and refresh an action. */
void func_0813388C(void)
{
    ActionState *state = &data_0200F3F0;

    state->flags &= ~0x20;
    if (func_08133A58(state->target, state->record->kind)) {
        const ActionDescriptor *descriptors = data_083A87B0;

        func_08142248(state, descriptors[state->record->kind].value);
        if (state->record->kind == 0x46) {
            u16 flags = state->flags;

            flags |= 0x200;
            state->flags = flags;
        }
        if (!(state->flags & 0x100)) {
            if (func_0812F358() == 1 || func_0812F358() == 2) {
                if (state->values[state->selected] > 0)
                    func_08131C28(state->record->kind, state->target);
                else if (descriptors[state->record->kind].mode < 0)
                    func_08131C28(state->record->kind, state->target);
            } else {
                func_08131C28(state->record->kind, state->target);
            }
            func_08130688(state->equipment_id, state->action_id, state->target);
        }
        func_08131C58(state->target);
        func_080CA2E8(state->target);
        func_080CA2E8(state->source);
    }
}
