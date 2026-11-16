#include "ffta.h"

/* Complete [0x080E29C4, 0x080E2BDC): 536 bytes, including the literal pool. */

typedef struct {
    u8 unknown_00[2];
    u8 palette;
    u8 unknown_03;
    s16 ages[8];
    void *objects[8];
} PieceState080E29C4;

typedef struct {
    const void *palette;
    u8 row;
    u8 unknown_05[3];
} PaletteEntry080E29C4;

typedef struct {
    u8 kind;
    u8 flags;
    s16 x;
    s16 y;
    u16 attributes;
    const void *resource;
} PieceEntry080E29C4;

typedef struct {
    u8 count;
    u8 unknown_01[3];
    PieceEntry080E29C4 pieces[4];
} PieceGroup080E29C4;

extern const PaletteEntry080E29C4 data_08395E64[];
extern const PieceGroup080E29C4 data_08395CC4[];

extern PieceState080E29C4 *func_08005BFC(void *task);
extern void func_08005BA8(void *task, u16 state);
extern void func_080D45D0(const void *palette, u8 slot, u8 bank, u8 first, u8 count);
extern s16 func_080D5FA4(void *const *entries, u16 count);
extern void *func_080D5CC0(const void *resource, u16 kind, s16 x, s16 y,
                           u16 attributes, u8 palette, u8 unknown, u32 flags);
extern void func_08011428(void *object);
extern void func_08011280(void *object, u8 value);

void func_080E29C4(void *task, s16 x, s16 y, u8 group, u8 palette)
{
    PieceState080E29C4 *state;
    const PieceEntry080E29C4 *piece;
    void *object;
    s16 age = 0;
    s16 slot;
    u8 i;
    u8 j;

    state = func_08005BFC(task);
    state->palette++;
    if (state->palette > 12)
        state->palette = 6;
    func_080D45D0(data_08395E64[palette].palette, state->palette, 1,
                  data_08395E64[palette].row, 1);

    for (i = 0; i < data_08395CC4[group].count; i++) {
        slot = func_080D5FA4(state->objects, 8);
        /* The ROM tests the result against zero and stores zero over it
         * (cmp r0, #0 at 0x080E2A4A; movs r1, #0 at 0x080E2A4E). */
        if (slot == 0)
            slot = 0;
        if (slot == -1) {
            for (slot = 0; slot < 8; slot++) {
                if (state->ages[slot] == 1) {
                    func_08011428(state->objects[slot]);
                    state->objects[slot] = 0;
                    state->ages[slot] = 0;
                    age = 8;
                    for (j = 0; j < 8; j++) {
                        state->ages[j]--;
                        if (state->ages[j] < 0)
                            state->ages[j] = 0;
                    }
                    break;
                }
            }
        } else {
            age = 0;
            for (j = 0; j < 8; j++) {
                if (state->ages[j] >= age)
                    age = state->ages[j] + 1;
            }
            /* The ROM spins when the new age exceeds 8 (cmp r0, #8 at
             * 0x080E2B32; b . at 0x080E2B36). */
            if (age > 8)
                while (1)
                    ;
        }

        piece = &data_08395CC4[group].pieces[i];
        object = func_080D5CC0(piece->resource, piece->kind,
                               x + piece->x, y + piece->y,
                               piece->attributes, state->palette, 0, 1);
        state->objects[slot] = object;
        if (piece->flags & 1)
            func_08011280(object, 1);
        state->ages[slot] = age;
    }
    func_08005BA8(task, 0x102);
}
