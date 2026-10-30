#include "ffta.h"

typedef struct {
    u8 field_00;
    u8 unknown_01;
    u16 field_02;
} Entry080CB24C;

typedef s32 (*Compare)(const void *first, const void *second);

extern Entry080CB24C g_state_02002B08[64];
extern s32 func_080CAA74(void);
extern void func_080028C8(void *workspace, void *base, s32 count, s32 size,
                          Compare compare);
extern s32 func_080CB634(const void *first, const void *second);

/* Complete [0x080CB24C, 0x080CB27C): 48 bytes, 17 instructions.
 * 10b581b0041cfff70ffc021c002a06d0054906480090201c042337f72ffb01b010bc01bc00470000082b000235b60c08
 */
void func_080CB24C(void **objects)
{
    s32 count = func_080CAA74();

    if (count != 0)
        func_080028C8(objects, g_state_02002B08, count,
                     sizeof(*g_state_02002B08), func_080CB634);
}
