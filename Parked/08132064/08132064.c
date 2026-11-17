#include "ffta.h"

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    u8 unknown_00[0xC];
    /* Elements 1..8 receive a random permutation of data_083A8C0C. */
    u8 order[9];
} Unit;

typedef struct {
    u8 unknown_00[8];
    Unit *unit;
    u8 unknown_0C[0x1A];
    u16 flags;
} FlaggedObject;

extern BufferCopier data_0836D4BC[];
extern const u8 data_083A8C0C[];
extern u32 func_08002804(void);
extern s32 func_08142950(s32 value, s32 divisor);

/* Complete [0x08132064, 0x081320E8): 132 bytes, pool words at 0x081320E0 and
 * 0x081320E4 (data_0836D4BC, data_083A8C0C).
 * f0b5474680b482b0071cf98c1020084000282cd1194c1a4923686846082210f0e5f8
 * 08250126a046d0f6bafb00040014291c10f05bfc031cb9680c3189196846c4182078
 * 0870e81a421e002a07d0581c6b46191840460368201c10f0c7f80136681e0006050e
 * 082e01dc002ddcd102b008bc9846f0bc01bc00470000bcd436080c8c3a08
 */
void func_08132064(FlaggedObject *object)
{
    u8 table[8];
    u8 count;
    s32 i;

    if (object->flags & 0x10)
        return;
    data_0836D4BC[0](table, data_083A8C0C, 8);
    count = 8;
    /* Both exits are in the ROM: cmp r6, #8; bgt at 0x081320CA and
     * cmp r5, #0; bne at 0x081320CE. */
    for (i = 1; i <= 8 && count != 0; i++, count--) {
        s32 index = func_08142950((s16)func_08002804(), count);
        s32 rest;

        object->unit->order[i] = table[index];
        rest = count - index - 1;
        if (rest != 0)
            data_0836D4BC[0](&table[index], &table[index + 1], rest);
    }
}
