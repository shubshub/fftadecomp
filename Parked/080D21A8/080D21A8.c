#include "ffta.h"

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
    s32 groupCount = func_080C9540(0x206) != 0;
    s32 count = 0;
    s32 group;
    s32 entry;
    s32 selected;

    if (func_080C9540(0x209))
        groupCount = 2;
    if (func_080C9540(0x20C))
        groupCount = 3;
    if (func_080C9540(0x211))
        groupCount = 4;
    if (func_080C9540(0x215))
        groupCount = 5;
    if (func_080C9540(0x21D))
        groupCount = 6;
    groupCount++;

    for (group = 0; group < groupCount; group++) {
        count++;
        for (entry = 0; entry < 20; entry++) {
            u16 identifier = g_table_08528E1C[group][entry];
            u16 flags = g_table_08528F34[identifier].flags;

            if (flags & 0x80)
                count++;
            if (flags & 0x40)
                count++;
        }
    }

    selected = (s16)func_08002804() % count;
    for (group = 0; group < groupCount; group++) {
        if (selected == 0)
            return group + 0xAB;
        selected--;
        for (entry = 0; entry < 20; entry++) {
            u16 identifier = g_table_08528E1C[group][entry];
            const ChoiceDescriptor *descriptor = &g_table_08528F34[identifier];

            if (descriptor->flags & 0x80) {
                if (selected == 0)
                    return identifier;
                selected--;
            }
            if (descriptor->flags & 0x40) {
                if (selected == 0)
                    return identifier + 0x55;
                selected--;
            }
        }
    }
    return 0;
}
