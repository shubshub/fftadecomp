#include "ffta.h"

typedef struct {
    u8 unknown_00[0x48];
} MenuList;

typedef struct {
    u8 unknown_00[0x78];
    MenuList list;
    u8 unknown_C0[0x0C];
} MenuRecord;

typedef struct {
    u8 unknown_000[0x954];
    MenuRecord records[1];
} MenuContext;

extern MenuContext *g_state_03002810;
extern u16 func_08017B50(MenuList *list);
extern void func_08042D4C(s32 slot, s16 item, MenuList *list);

/* Complete [0x08043070, 0x080430CC): 92 bytes, 38 reachable Thumb instructions.
 * f0b5474680b4061c11488046cc20371c47434146086838180e494018d4f760fd0004050c0024ac420dda0b483f182104091440460268d2197832301cfff74efe0134ac42f3db08bc9846f0bc01bc004710280003cc09000054090000
 */
void func_08043070(s32 slot)
{
    u16 count = func_08017B50(&g_state_03002810->records[slot].list);
    s32 item;

    for (item = 0; item < count; item++)
        func_08042D4C(slot, item, &g_state_03002810->records[slot].list);
}
