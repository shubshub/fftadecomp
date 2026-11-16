#include "ffta.h"

/* Complete [0x081130B8, 0x08113220): 360 bytes, 180 instructions.
 * Steps the two interpolations of each live record, moves its object, starts
 * a fresh overshooting leg when a leg ends, and culls the object once it has
 * left the screen.
 */

/* The interpolation state of func_080E0608/064C/0690, as their definitions
 * (src/080E0608.c) name it. */
typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    u8 mode;
    u8 unknown_01[3];
    Struct08011040 *object;
    u8 unknown_08[2];
    s16 delta_x;
    s16 delta_y;
    u8 duration_x;
    u8 duration_y;
    InterpolationState x;
    InterpolationState y;
} Record081130B8;

extern void func_080E0608(InterpolationState *state, s16 start, s16 end,
                          s16 duration);
extern void func_080E064C(InterpolationState *state);
extern u8 func_080E0690(InterpolationState *state);
extern void func_080107D4(void *object, s16 x, s16 y, s16 z);
extern void func_08011428(void *object);

void func_081130B8(Record081130B8 *records, u8 count)
{
    u8 index;

    for (index = 0; index < count; ++index) {
        if (records[index].object != 0) {
            u16 x;
            u16 y;
            u16 z;

            func_080E064C(&records[index].x);
            func_080E064C(&records[index].y);
            if (records[index].mode) {
                func_080107D4(records[index].object,
                    records[index].x.current >> 6,
                    records[index].y.current >> 6, 0);
                if (func_080E0690(&records[index].x))
                    func_080E0608(&records[index].x, records[index].x.current,
                        records[index].delta_x + (records[index].delta_x >> 2) +
                        records[index].x.current, records[index].duration_x);
                if (func_080E0690(&records[index].y))
                    func_080E0608(&records[index].y, records[index].y.current,
                        records[index].delta_y + (records[index].delta_y >> 2) +
                        records[index].y.current, records[index].duration_y);
            } else {
                func_080107D4(records[index].object,
                    records[index].x.current, records[index].y.current, 0);
                if (func_080E0690(&records[index].x))
                    func_080E0608(&records[index].x, records[index].x.current,
                        records[index].x.current + records[index].delta_x,
                        records[index].duration_x);
                if (func_080E0690(&records[index].y))
                    func_080E0608(&records[index].y, records[index].y.current,
                        records[index].y.current + records[index].delta_y,
                        records[index].duration_y);
            }
            func_08011040(records[index].object, &x, &y, &z);
            /* Two culling rules with one removal in the ROM: the block at
             * 0x081131FA is entered from the left/bottom tests (0x081131E2,
             * 0x081131EA) and from the right/top-in-mode test (0x081131F8),
             * and addresses the record through r4 from 0x081131C4 on every
             * entry. */
            if ((s16)x < -8 || (s16)y > 167) {
                func_08011428(records[index].object);
                records[index].object = 0;
            } else if (((s16)x > 247 || (s16)y < -8) && records[index].mode) {
                func_08011428(records[index].object);
                records[index].object = 0;
            }
        }
    }
}
