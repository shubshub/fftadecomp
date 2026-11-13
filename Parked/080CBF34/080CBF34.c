// Complete [0x080CBF34, 0x080CC0DC): 424 bytes.
// f0b557464e464546e0b481b036f760fc000400140b2176f001fd0a300006000e009000253a2081461749184a89188846009b9d4200d3a3e036f74afc00040014642176f0ebfc0006000e011c6a1c924640281fd84346ec180d4f0b4e36f738fc00040014142176f0d9fc0004001431784a464a43111c4018c0190078207000060028ebd052e000006a1f0002fa0e0000868c520859281dd84346ec180b4f0c4e36f716fc00040014142176f0b7fc0004001431784a464a43111c14314018c0190078207000060028ead02fe0868c52086a1f00025e291dd84346ec180b4f0c4e36f7f6fb00040014052176f097fc0004001431784a464a43111c28314018c0190078207000060028ead00fe0868c52086a1f00024346ea181249134b18784b464343181c2d3140180078107040462c18227811010d480818552a27d84188c0200840c02814d136f7c3fb00040114c00f081840104000091a09040914012915d120780ae0868c52086a1f0002348f520880200840002809d1101c5530207005e04246a918002008700135aa4653461806050e132d00d84be701b038bc9846a146aa46f0bc01bc0047

#include "ffta.h"

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

extern PickState080CBF34 data_02001F6A;
extern const u8 data_08528C86[][58];
extern const PickEntry080CBF34 g_table_08528F34[];
extern u16 func_08002804(void);
extern s32 func_08142950(s32 numerator, s32 denominator);

void func_080CBF34(void)
{
    u8 count;
    u8 i;
    u8 roll;
    u8 pick;
    const PickEntry080CBF34 *entry;

    count = func_08142950((s16)func_08002804(), 11) + 10;
    for (i = 0; i < 20; i++) {
        if (i < count) {
            roll = func_08142950((s16)func_08002804(), 100);
            if (roll <= 64) {
                do {
                    data_02001F6A.picks[i] = data_08528C86[data_02001F6A.table]
                        [(s16)func_08142950((s16)func_08002804(), 20)];
                } while (data_02001F6A.picks[i] == 0);
            } else if (roll <= 89) {
                do {
                    data_02001F6A.picks[i] = data_08528C86[data_02001F6A.table]
                        [(s16)func_08142950((s16)func_08002804(), 20) + 20];
                } while (data_02001F6A.picks[i] == 0);
            } else if (roll <= 94) {
                do {
                    data_02001F6A.picks[i] = data_08528C86[data_02001F6A.table]
                        [(s16)func_08142950((s16)func_08002804(), 5) + 40];
                } while (data_02001F6A.picks[i] == 0);
            } else {
                data_02001F6A.picks[i] = data_08528C86[data_02001F6A.table][45];
            }

            pick = data_02001F6A.picks[i];
            entry = &g_table_08528F34[pick];
            if (pick <= 0x55) {
                if ((entry->flags & 0xC0) == 0xC0) {
                    if ((s16)((s16)func_08002804() % 2) == 1)
                        data_02001F6A.picks[i] += 0x55;
                } else if (!(entry->flags & 0x80)) {
                    data_02001F6A.picks[i] = pick + 0x55;
                }
            }
        } else {
            data_02001F6A.picks[i] = 0;
        }
    }
}
