#include "ffta.h"

/* Complete [0x080A7218, 0x080A75BC): 932 bytes, including the thirteen-entry
 * jump table at 0x080A72A4 and the literal pools.  Steps the result built by
 * func_080A7138 (src/080A7138.c). */
typedef struct ValueUnit ValueUnit;

typedef struct {
    ValueUnit *unit;
    u8 unknown_04[4];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0E[0x11];
    s8 direction;
} UnitReference;

typedef struct {
    UnitReference *reference;
    u16 adjustment;
    u16 unknown_06;
} ValueEntry;

/* The 0x8C-byte result of func_080A7138. */
typedef struct {
    UnitReference *references[13];
    u16 count;
    u16 current;
    u16 delay;
    u8 unknown_3A[2];
    ValueEntry *entries;
    u8 index;
    u8 processed;
    u8 timer;
    u8 phase;
    u16 state;
    u16 depth;
    u16 stack[(0x8C - 0x48) / 2];
} ValueResult;

typedef struct {
    u8 unknown_00[0x16];
    u16 filtered_pressed;
} InputState;

extern u8 g_state_02000000[];
extern InputState g_state_0200F390;

extern s32 func_08025464(void);
extern void func_08029514(void);
extern void func_080A9270(void);
extern void func_080A9298(void);
extern void func_080A929C(void);
extern s32 func_080A9448(void);
extern void func_08025688(u16 identifier, u16 value, const void *argument);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern void func_08096F3C(s16 x, s16 y, s16 z);
extern u32 func_08096F7C(void);
extern void func_080A92E4(u16 mode, s16 x, s16 y, s16 z, u32 effect);
extern void func_08141780(float volume);
extern void func_08141570(s32 player_id, u16 song_id);
/* The call sign-extends both bytes (0x080A748C-0x080A7494), as the other
 * callers' s8 declarations do; the definition (src/0812F0E4.c) has u8. */
extern u8 func_0812F0E4(const ValueUnit *unit, s8 x, s8 z);
extern u8 func_080CD6A8(const void *object);
extern void func_0809A298(UnitReference *object, u16 value, s8 adjustment);
extern u32 func_08099C64(const void *owner);
extern void func_0809836C(void *object, u16 action, s8 value, u16 option);

u8 func_080A7218(ValueResult *result)
{
    switch (result->phase) {
    case 1:
        func_08025464();
        if (++result->timer > 15 && (g_state_0200F390.filtered_pressed & 3))
            result->timer = 120;
        if (result->timer >= 120) {
            result->timer = 0;
            func_08029514();
            result->phase = 2;
        }
        break;
    case 2:
        if ((u16)func_08025464()) {
            result->phase = 0;
            result->timer = 0;
        }
        break;
    }

    switch (result->state) {
    case 0:
        func_080A9270();
        result->state = 1;
        break;
    case 1:
        func_080A9298();
        result->state = 3;
        if (!(g_state_02000000[0x2FC1] & 1)) {
            result->stack[result->depth++] = result->state;
            result->state = 2;
        }
        break;
    case 3:
        if (!(g_state_02000000[0x2FC1] & 1)) {
            func_08025688(0x14, result->entries[result->index].adjustment, 0);
            result->phase = 1;
            result->timer = 0;
        }
        result->state = 4;
        break;
    case 4:
        if (result->phase != 0)
            break;
        for (result->current = 0; result->current < result->count;
             result->current++) {
            if (result->references[result->current] ==
                result->entries[result->index].reference) {
                result->state = 8;
                result->stack[result->depth++] = result->state;
                result->state = 6;
                return 1;
            }
        }
        /* fall through */
    case 5:
        if (++result->index >= result->processed) {
            result->state = 12;
        } else {
            result->state = 3;
            if (!(g_state_02000000[0x2FC1] & 1)) {
                result->stack[result->depth++] = result->state;
                result->state = 2;
            }
        }
        break;
    case 2:
        func_08096F3C(result->entries[result->index].reference->x,
                      result->entries[result->index].reference->y,
                      result->entries[result->index].reference->z);
        result->state = 7;
        break;
    case 6:
        func_08096F3C(result->references[result->current]->x,
                      result->references[result->current]->y,
                      result->references[result->current]->z);
        result->state = 7;
        break;
    case 7:
        if (!func_08096F7C())
            result->state = result->stack[--result->depth];
        break;
    case 8:
        if (result->phase != 0)
            break;
        if (!(g_state_02000000[0x2FC1] & 1)) {
            func_08025688(0x15, 0,
                          (const void *)func_080C7EA4(
                              result->references[result->current]->unit, 0));
            result->phase = 1;
        }
        result->timer = 0;
        result->state = 10;
        func_080A92E4(0, result->references[result->current]->x,
                      result->references[result->current]->y + 0x30,
                      result->references[result->current]->z, 0x17);
        func_08141780(0.5f);
        func_08141570(1, 8);
        if (!func_0812F0E4(result->references[result->current]->unit,
                           result->references[result->current]->x >> 5,
                           result->references[result->current]->z >> 5) ||
            func_080CD6A8(result->references[result->current]->unit)) {
            result->delay = 0x40;
            result->stack[result->depth++] = result->state;
            result->state = 11;
        } else {
            func_0809A298(result->references[result->current], 0x18,
                          result->references[result->current]->direction);
            result->stack[result->depth++] = result->state;
            result->state = 9;
        }
        break;
    case 9:
        if (!func_08099C64(result->references[result->current]))
            break;
        /* fall through */
    case 11:
        if (result->state == 11 && result->delay != 0) {
            result->delay--;
            break;
        }
        if (result->phase != 0)
            break;
        if (func_080A9448() != 0)
            break;
        func_08141780(1.0f);
        func_0809836C(result->references[result->current], 0,
                      result->references[result->current]->direction, 0);
        result->state = result->stack[--result->depth];
        break;
    case 10:
        if (result->phase == 0)
            result->state = 5;
        break;
    case 12:
        func_080A929C();
        return 0;
    }
    return 1;
}
