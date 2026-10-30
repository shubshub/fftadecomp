#include "ffta.h"

typedef struct ListObject080B4238 ListObject080B4238;

typedef struct {
    u8 unknown_0000[0x1554];
    ListObject080B4238 *field_1554;
    void *field_1558;
} State080B4238;

extern void func_08021BD4(ListObject080B4238 *child, void *object);
extern void func_08021B54(ListObject080B4238 *object);
extern void func_08022854(u8 *object);

/* Target [0x080B4238, 0x080B426C), 52 complete bytes:
 * 30b5051c002d0dd008482c182068084aa91809686df7c2fc2068
 * 6df77ffc281c6ef7fcfa30bc01bc004700005415000058150000
 */
void func_080B4238(State080B4238 *state)
{
    if (state != 0) {
        func_08021BD4(state->field_1554, state->field_1558);
        func_08021B54(state->field_1554);
        func_08022854((u8 *)state);
    }
}
