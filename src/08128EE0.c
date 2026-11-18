#include "ffta.h"

typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 unknown_06[10];
} UnitTemplate;

typedef struct {
    u8 unknown_0000[0x2E78];
    UnitTemplate templates[20];
} State;

extern State g_state_02000000;
extern UnitTemplate data_02002E78[];
extern const u32 g_table_085567F0[];
extern u32 func_08002804(void);
extern void func_080CC510(u8 index);
extern u32 func_080CCB68(u8 index);

u32 func_08128EE0(u8 mode)
{
    u8 active[20];
    u8 selected = 0;
    UnitTemplate *record = data_02002E78;
    int count = 0;
    int i;

    for (i = 0; i < 20; i++, record++)
        if (record->name)
            active[count++] = i;
    if (!count)
        return g_table_085567F0[744];
    switch (mode) {
    case 2:
        selected = active[(s16)func_08002804() % count];
        break;
    case 3: {
        u8 high = 0;
        for (i = 0; i < count; i++) {
            u8 index = active[i];
            if (g_state_02000000.templates[index].appearance >= high) {
                high = g_state_02000000.templates[index].appearance;
                selected = index;
            }
        }
        break;
    }
    default: {
        u8 low = 99;
        for (i = 0; i < count; i++) {
            u8 index = active[i];
            if (g_state_02000000.templates[index].appearance <= low) {
                low = g_state_02000000.templates[index].appearance;
                selected = index;
            }
        }
        break;
    }
    }
    func_080CC510(selected);
    return func_080CCB68(selected);
}
