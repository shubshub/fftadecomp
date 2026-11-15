#include "ffta.h"

/* Complete [0x0803616C, 0x08036282): 278 bytes, 129 instructions, five literal
 * words in two pools.
 * f0b557464e464546e0b4041c0d1c0026234882462349894601229046002751460868214a
 * 801800683a181078c3000020215e181f814260db183081425ddc5078c00084460022a95e
 * 0838814255db1830814252dc4846017801200840002801d1082e50d04a46117802200840
 * 002801d11b2e48d00021605e1a1c0832904217d10020295e60460830814211d151460868
 * 064a811808781d282dd8013008702ae010280003582e00027c0600003c0f000051460868
 * 05494018007800281bd10021605e904204da2088013005e03c0f0000904202dd20880138
 * 20800022a95e60460830814202da2888013003e0814202dd288801382880404606e00120
 * 8044143701361d2e8bdd002038bc9846a146aa46f0bc02bc0847
 *
 * Returns the 1-based index of the first of the 30 records with
 * record_x - 4 <= *x <= record_x + 20 and record_y - 8 <= *y <= record_y + 16
 * (the record's two bytes times eight), or 0 when there is none.  Index 8
 * returns 0 while bit 0 of the flag byte is clear and index 27 while bit 1 is
 * clear; func_08036350 (src/08036350.c) refuses the values 9 and 28 on the
 * same two bits.  When *x is record_x + 8 and *y is record_y + 8 the byte at
 * 0xF3C is raised by one, up to 30; otherwise, while that byte is zero, *x
 * and *y each step by one towards those values.
 */

/* The record and its member are declared as src/080376F4.c declares them. */
typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[18];
} PositionRecord;

/* The byte at 0xF3C is named as src/08037428.c names it. */
typedef struct {
    u8 unknown_000[0x67C];
    PositionRecord *records;
    u8 unknown_680[0x8BC];
    u8 cooldown;
} MenuContext;

/* The flag byte src/08036350.c reads at the same offset of the same object. */
typedef struct {
    u8 unknown_000[0x248];
    u8 flags;
} State0803616C;

extern MenuContext *g_state_03002810;
extern State0803616C g_state_02002C10;

u32 func_0803616C(s16 *x, s16 *y)
{
    s32 i;

    for (i = 0; i < 30; i++) {
        s32 record_x = g_state_03002810->records[i].x * 8;
        s32 record_y;

        if (*x < record_x - 4 || *x > record_x + 20)
            continue;
        record_y = g_state_03002810->records[i].y * 8;
        if (*y < record_y - 8 || *y > record_y + 16)
            continue;
        if (!(g_state_02002C10.flags & 1) && i == 8)
            return 0;
        if (!(g_state_02002C10.flags & 2) && i == 27)
            return 0;
        if (*x == record_x + 8 && *y == record_y + 8) {
            if (g_state_03002810->cooldown < 30)
                g_state_03002810->cooldown++;
            return i + 1;
        }
        if (g_state_03002810->cooldown == 0) {
            if (*x < record_x + 8)
                (*x)++;
            else if (*x > record_x + 8)
                (*x)--;
            if (*y < record_y + 8)
                (*y)++;
            else if (*y > record_y + 8)
                (*y)--;
        }
        return i + 1;
    }
    return 0;
}
