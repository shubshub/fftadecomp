#include "ffta.h"

/* Complete [0x080CBF34, 0x080CC0DC): 424 bytes, 180 instructions.
 * Target bytes:
 * f0b557464e464546e0b481b036f760fc000400140b2176f001fd0a300006000e00900025
 * 3a2081461749184a89188846009b9d4200d3a3e036f74afc00040014642176f0ebfc0006
 * 000e011c6a1c924640281fd84346ec180d4f0b4e36f738fc00040014142176f0d9fc0004
 * 001431784a464a43111c4018c0190078207000060028ebd052e000006a1f0002fa0e0000
 * 868c520859281dd84346ec180b4f0c4e36f716fc00040014142176f0b7fc000400143178
 * 4a464a43111c14314018c0190078207000060028ead02fe0868c52086a1f00025e291dd8
 * 4346ec180b4f0c4e36f7f6fb00040014052176f097fc0004001431784a464a43111c2831
 * 4018c0190078207000060028ead00fe0868c52086a1f00024346ea181249134b18784b46
 * 4343181c2d3140180078107040462c18227811010d480818552a27d84188c0200840c028
 * 14d136f7c3fb00040114c00f081840104000091a09040914012915d120780ae0868c5208
 * 6a1f0002348f520880200840002809d1101c5530207005e04246a918002008700135aa46
 * 53461806050e132d00d84be701b038bc9846a146aa46f0bc01bc0047
 *
 * Fills the 20 picks with 10 + rand % 11 draws from the selected row of the
 * 7 x 58-byte table at 0x08528C86 and clears the rest.  A roll out of 100
 * picks the column range: [0, 20), [20, 40), [40, 45) or the fixed column 45.
 *
 * The row byte and the picks share one base: the ROM loads 0x02001F6A as a
 * literal word in each arm (0x080CBF8E, 0x080CBFD2, 0x080CC012, 0x080CC04E)
 * and forms the picks as that word plus 0xEFA (0x080CBF5C-0x080CBF60).
 */
typedef struct {
    u8 table;
    u8 unknown_001[0xEF9];
    u8 picks[20];
} PickState080CBF34;

typedef struct {
    u8 unknown_00[2];
    u16 flags;
    u8 unknown_04[0xC];
} PickEntry080CBF34;

/* plausible: g_state_02000000 is reached as bytes plus an offset, as in
 * src/080C9540.c and src/08122EC0.c. */
extern u8 g_state_02000000[];
/* The pick state at g_state_02000000 + 0x1F6A: the ROM loads that address as
 * one literal word in each arm (0x080CBF8E, 0x080CBFD2, 0x080CC012,
 * 0x080CC04E) and forms the picks as that word plus 0xEFA (0x080CBF5C). */
#define PICK_STATE ((PickState080CBF34 *)(g_state_02000000 + 0x1F6A))
extern u8 data_08528C86[][58];
extern const PickEntry080CBF34 g_table_08528F34[];
extern u32 func_08002804(void);

/* Draws from columns [base, base + range) of the row into *slot until the
 * draw is non-zero.  The ROM has this block three times (0x080CBF88-0x080CBFB8,
 * 0x080CBFCC-0x080CBFFE, 0x080CC00C-0x080CC03E), differing only in the range
 * (20, 20, 5) and the column offset (0, 0x14, 0x28); each forms the slot
 * address before it loads the table addresses and tests the stored byte. */
#define DRAW_PICK(slot, range, base)                                \
    do {                                                            \
        *(slot) = data_08528C86[PICK_STATE->table]                \
            [(s16)((s16)func_08002804() % (range)) + (base)];       \
    } while (*(slot) == 0)

void func_080CBF34(void)
{
    u8 count;
    u8 i;
    u8 roll;
    const PickEntry080CBF34 *entry;

    count = (s16)func_08002804() % 11 + 10;
    for (i = 0; i < 20; i++) {
        if (i < count) {
            roll = (s16)func_08002804() % 100;
            if (roll <= 64)
                DRAW_PICK(&PICK_STATE->picks[i], 20, 0);
            else if (roll <= 89)
                DRAW_PICK(&PICK_STATE->picks[i], 20, 20);
            else if (roll <= 94)
                DRAW_PICK(&PICK_STATE->picks[i], 5, 40);
            else
                PICK_STATE->picks[i] = data_08528C86[PICK_STATE->table][45];

            entry = &g_table_08528F34[PICK_STATE->picks[i]];
            if (PICK_STATE->picks[i] <= 0x55) {
                if ((entry->flags & 0xC0) == 0xC0) {
                    if ((s16)((s16)func_08002804() % 2) == 1)
                        PICK_STATE->picks[i] += 0x55;
                } else if (!(entry->flags & 0x80)) {
                    PICK_STATE->picks[i] += 0x55;
                }
            }
        } else {
            PICK_STATE->picks[i] = 0;
        }
    }
}
