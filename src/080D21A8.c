#include "ffta.h"

/* Recovered from wowitsjack's parked attempt (Parked/080D21A8, 8f33d292bff).
 *
 * Complete [0x080D21A8, 0x080D2300): 344 bytes, 147 instructions.
 * Literal words at [0x080D227C, 0x080D2298) and [0x080D22BC, 0x080D22C0);
 * the halfword at 0x080D22BA is alignment.
 * f0b54f464646c0b43248f7f7c5f90006000e41420143cd0f2f48f7f7bdf90006
 * 002800d0022583208000f7f7b5f90006002800d003252948f7f7aef900060028
 * 00d004252648f7f7a7f90006002800d005252448f7f7a0f90006002800d00625
 * 002400260135a846464520da1e4881461e498c460134b000771c8019c0004946
 * 431813251a8810016044418880200840002800d0013440200840002800d00134
 * 0233013d002dedda3e1c4645e2db30f7d5fa00040014211c70f076fb031c0026
 * 464542dab44608488146002b10d1301cab302de0060200000902000011020000
 * 150200001d0200001c8e5208348f5208013b0025074f64464c4422881001c019
 * 418880200840002807d0002b04d1101c1ce00000348f5208013b1001c0194188
 * 40200840002807d0002b04d1101c55300004000c0ae0013b02340135132ddcdd
 * 28218c4401364645bfdb002018bc9846a146f0bc02bc0847
 */

/* One 16-byte row of the table func_080CCA20 (src/080CCA20.c) indexes with
 * the same identifiers this function returns. */
typedef struct {
    u8 unknown_00[2];
    u16 flags;
    u8 unknown_04[12];
} ChoiceDescriptor;

extern const u16 g_table_08528E1C[][20];
extern const ChoiceDescriptor g_table_08528F34[];

u8 func_080C9540(u16 bitIndex);
u32 func_08002804(void);

u16 func_080D21A8(void)
{
    s32 lastGroup;
    s32 count;
    s32 group;
    s32 entry;
    s32 selected;
    u16 identifier;

    lastGroup = 0;
    if (func_080C9540(0x206))
        lastGroup = 1;
    if (func_080C9540(0x209))
        lastGroup = 2;
    if (func_080C9540(0x20C))
        lastGroup = 3;
    if (func_080C9540(0x211))
        lastGroup = 4;
    if (func_080C9540(0x215))
        lastGroup = 5;
    if (func_080C9540(0x21D))
        lastGroup = 6;

    count = 0;
    for (group = 0; group < lastGroup + 1; group++) {
        count++;
        for (entry = 0; entry < 20; entry++) {
            identifier = g_table_08528E1C[group][entry];
            if (g_table_08528F34[identifier].flags & 0x80)
                count++;
            if (g_table_08528F34[identifier].flags & 0x40)
                count++;
        }
    }

    selected = (s16)func_08002804() % count;
    for (group = 0; group < lastGroup + 1; group++) {
        if (selected == 0)
            return group + 0xAB;
        selected--;
        for (entry = 0; entry < 20; entry++) {
            identifier = g_table_08528E1C[group][entry];
            if (g_table_08528F34[identifier].flags & 0x80) {
                if (selected == 0)
                    return identifier;
                selected--;
            }
            if (g_table_08528F34[identifier].flags & 0x40) {
                if (selected == 0)
                    return identifier + 0x55;
                selected--;
            }
        }
    }
    return 0;
}
