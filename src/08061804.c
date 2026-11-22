#include "ffta.h"

/* Complete [0x08061804, 0x08061BFC): 1016 bytes, 412 instructions, including
 * the switch table at 0x0806182C and the literal pools.
 * Target:
 * f0b5474680b40649086803780a1c0b2b00d9d5e1980003494018006887460000
 * 50f400022c1806085c180608c41b0608c41b0608c41b0608c41b0608c41b0608
 * c41b0608c41b0608841a0608a81a06080c1b0608401b0608324e3368586d1121
 * 494208405865304994310a882f48104008802f4880461a182e4d281caf300178
 * c800401a80002c4c29194018106028602a496818006801273840002800d1c5e0
 * 281cce300488264aa0180004000c012167f05efe30681e494018026821482418
 * 381ca040518b0843508303f0adfa0006002804d103f0bcfa0006002834d03268
 * 111c4e31b1200880092414805088411c51800004c00b131d1818048034241480
 * 5088411c51800004c00b1b181c803320108042441268907d622800d9a6e00130
 * 9075a3e050f4000290f30002fffe000088080000d020000278080000541b0000
 * ff02000093feffff17496818174aa91800780978401a0006002829db3268111c
 * 4e31b3200880092414805088411c51800004c00b131d18180480342414805088
 * 411c51800004c00b1b181c803320108042441268107e622801d8013010760120
 * 6cf0caff62e00000ce1b0000cf1b00003268111c4e31b42008800b2414805088
 * 411c51800004c00b131d18180480342414805088411c51800004c00b1b181c80
 * 3320108042441268507e622801d8013050760a48002167f0bbfd0948002167f0
 * b7fd0848002167f0b3fd0748012167f0affd00206cf090ff28e00000a1050000
 * a2050000a3050000a9050000191c4e31b22008801168c87d622801d80130c875
 * 32680b2414805088411c51800004c00b131d18180480342414805088411c5180
 * 0004c00b1b181c803320108003480268506d022108435065a8e0000050f40002
 * 0648074c0019002303801268506d082108435065538013800220a4e000000002
 * 9e21000003f084f915490006000e8881144a10684d300b210170106851309021
 * 017012685088411c51800004c00b131d1818118801800a2414805088411c5180
 * 0004c00b18180480372414805088411c51800004c00b1b181c803120108065e0
 * d020000250f400020b4c20685130102101702068406c04f085fa22680b231380
 * 5188481c50800904c90b101d40180380322010804ae0000050f400021f480268
 * 111c4e31cb200880082414805088411c51800004c00b131d1818048037241480
 * 5088411c51800004c00b18180480342515805088411c51800004c00b18180580
 * 362414805088411c51800004c00b181804803c2414805088411c51800004c00b
 * 1818048015805088411c51800004c00b1b181d803520108008e0000050f40002
 * 0b48990009180868e0f03afb09480068406d02210840002801d0b0f73ff80020
 * 03f020fa002008bc9846f0bc02bc08471839390850f40002
 *
 * Phase dispatcher of the script state at 0x0200F450: phases 0 and 8-11 are
 * handled here, every other phase calls its entry in data_08393918 (as
 * src/080617C4.c does).  The caller, src/080615E0.c, reads the result: 2 after
 * phase 8, else 0.
 */

typedef struct {
    u8 text[0x14];
    u8 status;
    u8 age;
    u8 count_16;
    u8 count_17;
    u8 count_18;
    u8 count_19;
    u16 flags;
} Entry08061804;

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[5];
    u8 marker;
    u16 message;
    u8 mode;
    u8 timer;
    u8 unknown_52[2];
    u32 flags;
    u8 unknown_58[0x830];
    Entry08061804 *entry;
} CommandState;

typedef struct {
    Entry08061804 *current;
    u8 unknown_04[8];
    u16 field_0c;
    u8 unknown_0e[0xA1];
    u8 selected;
    u8 unknown_b0[0x1E];
    u16 item;
    u8 unknown_d0[0x7A8];
    Entry08061804 entries[16];
    u8 unknown_a38[0x111C];
    u32 flags;
    u8 unknown_1b58[0x76];
    u8 value_1bce;
    u8 value_1bcf;
} Cache08061804;

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} Control08061804;

typedef struct {
    u8 unknown_00[0x219E];
    u16 item;           /* the halfword at 0x020020D0 + 0xCE */
} Global08061804;

extern CommandState *data_0200F450;
extern Cache08061804 g_state_020020D0;
extern Control08061804 g_state_0200F390;
extern Global08061804 g_state_02000000;
extern void (*data_08393918[])(void);
extern void func_080C9574(u16 index, u16 enabled);
extern u8 func_08064E2C(void);
extern u8 func_08064E54(void);
extern void func_080CE93C(u8 reset);
extern u8 func_08064DB4(void);
extern void func_08066028(void *context);
extern void func_08011C60(void);
extern void func_08065028(u32 value);

/* The run-list push of src/080633F8.c and src/080629DC.c. */
static inline void queue_command(CommandState *state, u16 command)
{
    state->current = command;
    state->entries[state->count++] = state->current;
}

u8 func_08061804(void)
{
    u8 selector = data_0200F450->current;

    switch (selector) {
    case 0: {
        /* Read through this local here and in the 0xB2 arm, and through
         * data_0200F450 elsewhere, as src/08064004.c and src/0806216C.c
         * mix the two.  With direct reads throughout the loads are the same
         * (r3 at 0x0806185E and the +0x888 address in r2 at 0x0806187A are
         * reused in the 0xB2 arm either way); only r6 and r7 swap
         * (0x0806185C-0x08061A44). */
        CommandState *state = data_0200F450;

        state->flags &= ~0x10;
        g_state_0200F390.flags &= ~0x100;
        state->entry = &g_state_020020D0.entries[g_state_020020D0.selected];
        g_state_020020D0.current = state->entry;
        if (g_state_020020D0.flags & 1) {
            u16 item = g_state_020020D0.item;

            func_080C9574(item + 0x2FF, 1);
            data_0200F450->entry->flags |= 1 << (item - 0x16D);
            if (func_08064E2C() || func_08064E54()) {
                data_0200F450->message = 0xB1;
                queue_command(data_0200F450, 9);
                queue_command(data_0200F450, 0x34);
                data_0200F450->current = 0x33;
                if (data_0200F450->entry->count_16 < 99)
                    data_0200F450->entry->count_16++;
            } else if ((s8)(g_state_020020D0.value_1bce - g_state_020020D0.value_1bcf) >= 0) {
                data_0200F450->message = 0xB3;
                queue_command(data_0200F450, 9);
                queue_command(data_0200F450, 0x34);
                data_0200F450->current = 0x33;
                if (data_0200F450->entry->count_18 < 99)
                    data_0200F450->entry->count_18++;
                func_080CE93C(1);
            } else {
                data_0200F450->message = 0xB4;
                queue_command(data_0200F450, 0xB);
                queue_command(data_0200F450, 0x34);
                data_0200F450->current = 0x33;
                if (data_0200F450->entry->count_19 < 99)
                    data_0200F450->entry->count_19++;
                func_080C9574(0x5A1, 0);
                func_080C9574(0x5A2, 0);
                func_080C9574(0x5A3, 0);
                func_080C9574(0x5A9, 1);
                func_080CE93C(0);
            }
        } else {
            state->message = 0xB2;
            if (state->entry->count_17 < 99)
                state->entry->count_17++;
            queue_command(data_0200F450, 0xB);
            queue_command(data_0200F450, 0x34);
            data_0200F450->current = 0x33;
        }
        data_0200F450->flags |= 2;
        break;
    }
    case 8:
        g_state_02000000.item = 0;
        data_0200F450->flags |= 8;
        data_0200F450->count = 0;
        data_0200F450->current = 0;
        return 2;
    case 9:
        g_state_020020D0.field_0c = func_08064DB4();
        data_0200F450->marker = 0xB;
        data_0200F450->timer = 0x90;
        data_0200F450->entries[data_0200F450->count++] = data_0200F450->current;
        queue_command(data_0200F450, 0xA);
        queue_command(data_0200F450, 0x37);
        data_0200F450->current = 0x31;
        break;
    case 10:
        data_0200F450->timer = 0x10;
        func_08066028(data_0200F450->context);
        queue_command(data_0200F450, 0xB);
        data_0200F450->current = 0x32;
        break;
    case 11:
        data_0200F450->message = 0xCB;
        queue_command(data_0200F450, 8);
        queue_command(data_0200F450, 0x37);
        queue_command(data_0200F450, 0x34);
        queue_command(data_0200F450, 0x36);
        queue_command(data_0200F450, 0x3C);
        queue_command(data_0200F450, 0x34);
        data_0200F450->current = 0x35;
        break;
    default:
        data_08393918[selector]();
        break;
    }
    if (data_0200F450->flags & 2)
        func_08011C60();
    func_08065028(0);
    return 0;
}
