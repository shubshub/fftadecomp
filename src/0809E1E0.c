#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 hp;
    u8 unknown_1A[0xB6];
    s16 readiness;
    u8 unknown_D2[2];
    s16 bonus;
    u8 unknown_D6[0x32];
} Unit0809E1E0;

typedef struct {
    s32 count;
    Unit0809E1E0 records[13];
    u8 unknown_D6C[0x68];
    u32 saved_values[13];
} State0809E1E0;

extern s32 func_0809E05C(State0809E1E0 *state);
extern void func_08097298(Unit0809E1E0 *unit);
extern u8 func_080C8280(Unit0809E1E0 *unit);
extern void func_080CD7F0(Unit0809E1E0 *unit);
extern u8 func_080CD8CC(Unit0809E1E0 *unit);
extern u8 func_080CD8E4(Unit0809E1E0 *unit);
extern u8 func_080CD95C(Unit0809E1E0 *unit);
extern u8 func_080CD974(Unit0809E1E0 *unit);
extern u8 func_080CDA04(Unit0809E1E0 *unit);
extern u8 func_080CDA94(Unit0809E1E0 *unit);
extern u8 func_080CDADC(Unit0809E1E0 *unit);
extern u8 func_080CDAF4(Unit0809E1E0 *unit);
extern u8 func_080CDB0C(Unit0809E1E0 *unit);
extern u8 func_080CDB24(Unit0809E1E0 *unit);
extern u8 func_080CDB3C(Unit0809E1E0 *unit);
extern u8 func_080CDB54(Unit0809E1E0 *unit);
extern u8 func_080CDB6C(Unit0809E1E0 *unit);
extern u8 func_080CDB84(Unit0809E1E0 *unit);
extern u8 func_080CDB9C(Unit0809E1E0 *unit);
extern u8 func_080CDBB4(Unit0809E1E0 *unit);
extern void func_080CDD1C(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDD40(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDD64(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDE14(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDE38(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDEC8(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDF10(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDF78(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDF9C(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CDFE4(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE050(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE070(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE094(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE0B8(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE0DC(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE100(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE124(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE148(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE16C(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE18C(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE1B0(Unit0809E1E0 *unit, u8 enabled);
extern void func_080CE2F0(Unit0809E1E0 *unit, u8 enabled);
extern u8 func_080CE3A0(Unit0809E1E0 *unit);
extern u8 func_080CE3A8(Unit0809E1E0 *unit);
extern u8 func_080CE3B0(Unit0809E1E0 *unit);
extern u8 func_080CE3B8(Unit0809E1E0 *unit);
extern u8 func_080CE3C0(Unit0809E1E0 *unit);
extern u8 func_080CE3C8(Unit0809E1E0 *unit);
extern u8 func_080CE3D0(Unit0809E1E0 *unit);
extern u8 func_080CE3D8(Unit0809E1E0 *unit);
extern u8 func_080CE3E0(Unit0809E1E0 *unit);
extern u8 func_080CE3E8(Unit0809E1E0 *unit);
extern u8 func_080CE3F0(Unit0809E1E0 *unit);
extern u8 func_080CE3F8(Unit0809E1E0 *unit);
extern u8 func_080CE400(Unit0809E1E0 *unit);
extern u8 func_080CE408(Unit0809E1E0 *unit);
extern void func_080CE418(Unit0809E1E0 *unit, u8 value);
extern void func_080CE420(Unit0809E1E0 *unit, u8 value);
extern void func_080CE438(Unit0809E1E0 *unit, u8 value);
extern void func_080CE440(Unit0809E1E0 *unit, u8 value);
extern void func_080CE448(Unit0809E1E0 *unit, u8 value);
extern void func_080CE450(Unit0809E1E0 *unit, u8 value);
extern void func_080CE458(Unit0809E1E0 *unit, u8 value);
extern void func_080CE460(Unit0809E1E0 *unit, u8 value);
extern void func_080CE468(Unit0809E1E0 *unit, u8 value);
extern void func_080CE470(Unit0809E1E0 *unit, u8 value);
extern void func_080CE478(Unit0809E1E0 *unit, u8 value);
extern void func_080CE480(Unit0809E1E0 *unit, u8 value);
extern u8 func_08131030(Unit0809E1E0 *unit);
extern void func_08133BB4(Unit0809E1E0 *unit, u32 value);

/*
 * Tick one status counter: if the status is active, count it down, and when
 * it runs out clear the status and record its bit in the unit's saved value.
 * The ROM has this block ten times (0x0809E276-0x0809E2C0, then nine in a row
 * at 0x0809E422-0x0809E732) in the same instructions and registers; only the
 * four callees, the flag constant and the first block's unit-address
 * arithmetic differ.  The fall-through `movs r5, #0` (e.g. 0x0809E290) is
 * the `count <= 0` arm; count is a zero-extended byte
 * (0x0809E288-0x0809E28A), so that arm only rewrites a zero.  The `bgt` tests
 * (0x0809E28E, 0x0809E298) are signed compares of an int count.
 */
#define COUNT_DOWN(active, get, set, clear, flag)                   \
    if (active(&state->records[i])) {                               \
        count = get(&state->records[i]);                            \
        if (count <= 0)                                             \
            count = 0;                                              \
        else if (--count <= 0) {                                    \
            clear(&state->records[i], 0);                           \
            state->saved_values[i] |= (flag);                       \
        }                                                           \
        set(&state->records[i], count);                             \
    }

/* Complete target [0x0809E1E0, 0x0809E82E): 1614 bytes, 725 instructions. */
u32 func_0809E1E0(State0809E1E0 *state)
{
    s32 i;
    s32 count;
    u8 countdown_a;
    u8 countdown_b;

    /*
     * The exit tests of the else arm at the end (hp not zero; 0x0809E1F8)
     * and the readiness reset (0x0809E246) sit ahead of the body, entered by
     * the branch at 0x0809E1F2: gcc's loop-exit rotation of this for (;;),
     * not source order.
     */
    for (;;) {
        i = func_0809E05C(state);
        func_080CE2F0(&state->records[i], 0);
        COUNT_DOWN(func_080CDADC, func_080CE3C0, func_080CE438, func_080CE050, 8);

        if (!func_080CDADC(&state->records[i])) {
            if (func_080CDA04(&state->records[i])) {
                if (func_080CD95C(&state->records[i])) {
                    func_080CDE14(&state->records[i], 0);
                    state->saved_values[i] |= 0x8000;
                }
                func_08133BB4(&state->records[i], 0x2E);
                func_080CDF10(&state->records[i], 0);
                state->saved_values[i] |= 0x4000;
            }
            if (func_080CDA94(&state->records[i])) {
                count = func_080CE3A8(&state->records[i]);
                /* The same zero clamp: movs r5, #0 at 0x0809E34E. */
                if (count <= 0)
                    count = 0;
                else if (--count <= 0) {
                    u8 enabled = func_080CD8CC(&state->records[i]);

                    state->saved_values[i] |= 1;
                    func_080CDFE4(&state->records[i], 0);
                    func_08097298(&state->records[i]);
                    func_080CDD40(&state->records[i], enabled);
                }
                func_080CE420(&state->records[i], count);
            }
        }

        func_080CDD1C(&state->records[i], 0);
        if (!func_080CDADC(&state->records[i])) {
            func_080CDEC8(&state->records[i], 0);
            func_080CDF78(&state->records[i], 0);
            func_080CDF9C(&state->records[i], 0);
            func_080CE1B0(&state->records[i], 0);
            if (func_080CD8E4(&state->records[i]) && state->records[i].hp == 0)
                func_080CDD64(&state->records[i], 0);
            if (func_080CD974(&state->records[i]) && state->records[i].hp == 0)
                func_080CDE38(&state->records[i], 0);
            COUNT_DOWN(func_080CDAF4, func_080CE3C8, func_080CE440, func_080CE070, 0x10);
            COUNT_DOWN(func_080CDB0C, func_080CE3D0, func_080CE448, func_080CE094, 0x20);
            COUNT_DOWN(func_080CDB3C, func_080CE3E0, func_080CE458, func_080CE0DC, 0x80);
            COUNT_DOWN(func_080CDB84, func_080CE3F8, func_080CE470, func_080CE148, 0x400);
            COUNT_DOWN(func_080CDB9C, func_080CE400, func_080CE478, func_080CE16C, 0x800);
            COUNT_DOWN(func_080CDBB4, func_080CE408, func_080CE480, func_080CE18C, 0x1000);
            COUNT_DOWN(func_080CDB24, func_080CE3D8, func_080CE450, func_080CE0B8, 0x40);
            COUNT_DOWN(func_080CDB54, func_080CE3E8, func_080CE460, func_080CE100, 0x100);
            COUNT_DOWN(func_080CDB6C, func_080CE3F0, func_080CE468, func_080CE124, 0x200);

            countdown_a = func_080CE3B0(&state->records[i]);
            countdown_b = func_080CE3B8(&state->records[i]);
            func_080CD7F0(&state->records[i]);
            if (!func_080CE3B0(&state->records[i]) && countdown_a)
                state->saved_values[i] |= 2;
            if (!func_080CE3B8(&state->records[i]) && countdown_b)
                state->saved_values[i] |= 4;
        }

        if (func_08131030(&state->records[i]) && func_080C8280(&state->records[i])) {
            count = func_080CE3A0(&state->records[i]);
            /* The same zero clamp: movs r5, #0 at 0x0809E7C8. */
            if (count <= 0)
                count = 0;
            else if (--count <= 0)
                state->saved_values[i] |= 0x2000;
            func_080CE418(&state->records[i], count);
        }

        if (func_080C8280(&state->records[i])) {
            if (state->saved_values[i] & 0x2000)
                break;
        } else {
            if (!func_080CDADC(&state->records[i]) &&
                (func_080CD8E4(&state->records[i]) || func_080CD974(&state->records[i])))
                break;
            if (!func_080CDB24(&state->records[i]) && !func_080CDADC(&state->records[i]))
                break;
            if (state->saved_values[i])
                break;
        }
        state->records[i].readiness = 0;
        state->records[i].bonus = 0;
    }
    return i;
}
