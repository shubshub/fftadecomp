#include "ffta.h"

typedef struct {
    u32 identifier;
    u8 active;
    u8 kind;
    u8 unknown_06[2];
    u16 value_14 : 10;
    u16 value_16 : 10;
    u16 value_17 : 11;
    u16 value_18 : 11;
    u16 value_19 : 11;
    u16 value_1A : 11;
} __attribute__((packed)) PackedValues;

typedef struct {
    void *source;
    u8 unknown_04[4];
    const void *target;
    u8 unknown_0C[0x1A];
    u16 flags;
} State0813347C;

extern u8 func_08131BB8(void *record);
extern PackedValues *func_0812F124(const void *object);
extern void func_0812EBD0(PackedValues *destination, const void *source);
extern u32 func_0812EDF0(const void *object);
extern s32 func_080CA900(u16 identifier, u8 quantity);
extern void func_080C9574(u16 bitIndex, u16 enabled);

/* Complete 0x0813347C..0x081334CC, 80 bytes:
 * 10b5041ce18c1020084000281ad140200843e0842068fef791fb000600280dd0a068
 * fbf741fea168fbf794fba068fbf7a1fc0004000c012197f724fa0348012196f75af8
 * 10bc01bc00470000ab050000
 */
void func_0813347C(State0813347C *state)
{
    if (!(state->flags & 0x10)) {
        state->flags |= 0x40;
        if (func_08131BB8(state->source)) {
            PackedValues *destination = func_0812F124(state->target);

            func_0812EBD0(destination, state->target);
            func_080CA900((u16)func_0812EDF0(state->target), 1);
        }
        func_080C9574(0x5AB, 1);
    }
}
