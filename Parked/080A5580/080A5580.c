#include "ffta.h"

/* Complete [0x080A5580, 0x080A5992): 1042 bytes, 390 instructions. */

typedef struct {
    u8 unknown_00[0xF8];
    s8 facing;
} Unit080A5580;

typedef struct {
    Unit080A5580 *unit;
    u8 unknown_04[4];
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_0E[0x11];
    s8 facing;
} Object080A5580;

typedef struct {
    Object080A5580 *object;
    u8 unknown_04[4];
    void *secondary_task;
    u16 flags;
    u16 type;
    u8 unknown_10[0x0E];
    s16 first_effect;
    s16 second_effect;
    u8 unknown_22[0x0A];
} Entry080A5580;

typedef struct {
    Object080A5580 *primary;
    u8 unknown_04[6];
    u8 offset_x;
    u8 offset_y;
    u8 unknown_0C[4];
    u16 enabled;
    u16 item;
    s16 x;
    s16 height;
    s16 y;
    u8 unknown_1A[6];
    Entry080A5580 entries[15];
    u8 unknown_2B4[0x0C];
    u8 count;
} State080A5580;

extern u8 func_0812EE98(void *unit, u16 entry);
extern void func_080A92E4(s32 mode, s32 x, s32 height, s32 y, s32 effect);
extern void func_08141570(s32 group, s32 sound);
extern void func_08141520(u16 sound);
extern s32 func_0809D6BC(s8 dx, s8 dy);
extern void func_0809836C(Object080A5580 *object, u16 action, s8 direction,
                          u16 option);
extern void func_080A1D84(s8 first, s8 second, s8 *left, s8 *right);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern void func_0809D854(Object080A5580 *object, u32 selector, u32 value);
extern s32 func_080CA7A4(u16 entry, u8 selector);

void func_080A5580(State080A5580 *state)
{
    s32 played = 0;
    s32 hit = 0;
    s32 moved = 0;
    s32 i;
    s32 direction;
    s8 left;
    s8 right;

    if (state->count == 0 && state->enabled == 0) {
        if (func_0812EE98(state->primary->unit, state->item) == 0x0D ||
            func_0812EE98(state->primary->unit, state->item) == 0x0E ||
            func_0812EE98(state->primary->unit, state->item) == 0x13) {
            func_080A92E4(0, state->x, state->height, state->y, 0x15);
            func_08141570(2, 0x8D);
        }
    }

    for (i = 0; i < state->count; i++) {
        switch (state->entries[i].type) {
        case 3:
        case 4:
            direction = func_0809D6BC(
                (s8)((state->primary->x >> 5) - state->offset_x),
                (s8)((state->primary->y >> 5) - state->offset_y));
            func_0809836C(state->entries[i].object, 3, direction, 0);
            state->entries[i].object->unit->facing =
                state->entries[i].object->facing;
            func_08141570(1, 0xEC);
            break;
        case 1:
            hit = 1;
            if (state->entries[i].flags & 0x20)
                played = 1;
            func_0809836C(state->entries[i].object, 5,
                          state->entries[i].object->facing, 0);
            func_080A1D84(state->primary->facing,
                          state->entries[i].object->facing, &left, &right);
            if (left)
                func_0809A570(state->entries[i].object, 0, 0x200);
            if (right)
                func_0809A570(state->entries[i].object, 0, 0x400);
            break;
        case 2:
            if (state->entries[i].secondary_task == 0) {
                direction = func_0809D6BC(
                    (s8)((state->primary->x >> 5) - state->offset_x),
                    (s8)((state->primary->y >> 5) - state->offset_y));
                func_0809836C(state->entries[i].object, 4, direction, 0);
                state->entries[i].object->unit->facing =
                    state->entries[i].object->facing;
            }
            if (state->item != 0) {
                switch (func_0812EE98(state->primary->unit, state->item)) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 15:
                    moved = 1;
                    break;
                /* A second group with the same store: the ROM table sends
                 * these cases to 0x080A57A2, the first group to 0x080A579C. */
                case 10:
                case 11:
                case 12:
                case 14:
                case 16:
                case 17:
                case 18:
                    moved = 1;
                    break;
                }
            } else {
                moved = 1;
            }
            func_0809D854(state->entries[i].object, state->primary->facing, 3);
            break;
        }
        if (state->entries[i].flags & 0x20)
            func_080A92E4(0, state->entries[i].object->x,
                          state->entries[i].object->height,
                          state->entries[i].object->y, 0x14);
        if (state->entries[i].flags & 1)
            func_080A92E4(state->entries[i].first_effect,
                          state->entries[i].object->x,
                          (s16)(state->entries[i].object->height + 0x30),
                          state->entries[i].object->y, 0);
        if (state->entries[i].flags & 2)
            func_080A92E4(state->entries[i].second_effect,
                          state->entries[i].object->x,
                          (s16)(state->entries[i].object->height + 0x30),
                          state->entries[i].object->y, 0);
    }

    if (!hit) {
        if (moved == 1)
            func_08141520(0x85);
    } else if (played) {
        func_08141520(0x8B);
    } else {
        u16 item = state->item;
        s32 kind;

        if (item == 0)
            kind = -1;
        else
            kind = func_080CA7A4(item, 3);
        switch (kind) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
            func_08141520(0x7B);
            break;
        case 8:
        case 15:
            func_08141520(0x7C);
            break;
        case 10:
        case 11:
        case 12:
            func_08141520(0x7D);
            break;
        case 13:
        case 14:
            func_08141520(0x8A);
            break;
        case 16:
            switch (item) {
            case 0xCE:
            case 0xCF:
            case 0xD1:
                func_08141520(0x83);
                break;
            case 0xD0:
            case 0xD3:
                func_08141520(0x84);
                break;
            case 0xCB:
                func_08141520(0x82);
                break;
            default:
                func_08141520(0x81);
                break;
            }
            break;
        case 19:
            break;
        default:
            func_08141520(0x7E);
            break;
        }
    }
}
