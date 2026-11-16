#include "ffta.h"

/* Complete [0x08061C30, 0x08061C9C): 108 bytes, 45 instructions, including
 * the two-word literal pool at 0x08061C94.
 * Target: 30b581b06420c0f703fe051c4020c0f7fffd041c1348d22149004018211c3c31
 * 08601c380439a142fada0f480090281c211c10220423a0f72ffe002188000019
 * 0268507d0131002800d051750f29f5dd201cc0f7e7fd281cc0f7e4fd01b030bc
 * 01bc004748290002251c0608
 *
 * Sorts a table of pointers to the sixteen 28-byte cache entries at
 * data_02002948 by age (+0x15; func_08061C24 compares through the pointers),
 * then sets each non-zero age to its 1-based position in the sorted order.
 * The entry layout is the caller's, src/08061C9C.c (g_state_020020D0 + 0x878).
 *
 * The fill is the ascending loop; loop.c reverses it ("Reversed loop and
 * added reg_nonneg", -dL), reduces its givs and eliminates the counter,
 * which gives the ROM's descending stores (0x08061C50..0x08061C54) and the
 * cursor-against-base compare at 0x08061C56.  A descending source loop keeps
 * a counter (116 bytes).
 */

typedef struct {
    u8 text[0x14];
    u8 status;
    u8 age;
    u8 unknown_16[6];
} Entry08061C9C;

typedef s32 (*Compare)(const void *first, const void *second);

extern Entry08061C9C data_02002948[16];
extern void *func_08022840(u32 size);
extern void func_08022854(void *object);
extern void func_080028C8(void *workspace, void *base, s32 count, s32 size,
                          Compare compare);
extern s32 func_08061C24(const void *left, const void *right);

void func_08061C30(void)
{
    void *workspace = func_08022840(100);
    Entry08061C9C **order = func_08022840(16 * sizeof(*order));
    s32 i;

    for (i = 0; i < 16; i++)
        order[i] = &data_02002948[i];
    func_080028C8(workspace, order, 16, sizeof(*order), func_08061C24);
    for (i = 0; i < 16; i++) {
        if (order[i]->age != 0)
            order[i]->age = i + 1;
    }
    func_08022854(order);
    func_08022854(workspace);
}
