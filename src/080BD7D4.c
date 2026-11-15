#include "ffta.h"

/* func_080BD7D4 - complete [0x080BD7D4, 0x080BD8CA): 246 bytes, 121 instructions.
 * Target:
 *   f0b557464e464546e0b487b08046009101920068011cf63109780391f73000780490012002904146
 *   803106911b060593039a029bd61a049f0124a24601204042814630060516380604164046291c221c
 *   ff23dcf797fb00281cd041460868f63006700868f7300770069a1068291c221c059c2316fff788fd
 *   000642461168f6316b461b7b0b701168f7316c46247c0c70002824d00398b04202d10499b9421ad0
 *   56444f44039a964209d14b465b4299465446012c03d10120404281450bd004988742bed151464942
 *   8a460129b9d1012040428145b5d1029a01320292a8e7009b1e70019c277007b038bc9846a146aa46
 *   f0bc01bc0047
 *
 * Walks the diamond rings of radius 1, 2, ... around the unit's position and
 * stores the first cell that func_08099F58 accepts and for which
 * func_080BD35C, called with the unit's position temporarily set to that
 * cell, returns zero.  The ring walk is the one in func_080B44F8 and
 * func_080C127C.
 */
typedef struct {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
} Unit;

typedef struct {
    Unit *unit;
    u8 unknown_04[0x7C];
    void *world;
} Context;

extern s32 func_08099F58(Context *context, s8 x, s8 y, u8 range);
extern u8 func_080BD35C(void *world, s8 x, s8 y, s8 length);

void func_080BD7D4(Context *context, u8 *output_x, u8 *output_y, s8 length)
{
    s32 radius;
    u8 original_x = context->unit->x;
    u8 original_y = context->unit->y;
    s32 x;
    s32 y;
    s32 step_x;
    s32 step_y;

    for (radius = 1; ; radius++) {
        x = original_x - radius;
        y = original_y;
        step_x = 1;
        step_y = -1;

        while (1) {
            if (func_08099F58(context, x, y, 0xFF)) {
                u8 blocked;

                context->unit->x = x;
                context->unit->y = y;
                blocked = func_080BD35C(context->world, x, y, length);
                context->unit->x = original_x;
                context->unit->y = original_y;
                if (!blocked) {
                    *output_x = x;
                    *output_y = y;
                    return;
                }
            }

            if (original_x == x && original_y == y)
                break;
            x += step_x;
            y += step_y;
            if (x == original_x) {
                step_y = -step_y;
                if (step_x == 1 && step_y == -1)
                    break;
            }
            if (y == original_y) {
                step_x = -step_x;
                if (step_x == 1 && step_y == -1)
                    break;
            }
        }
    }
}
