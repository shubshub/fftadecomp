#include "history_unit.h"

typedef struct {
    u8 unknown_00[0x30];
} UnitSource;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    UnitSource *sources;
    u8 unknown_08[0x20];
} UnitGroup;

extern UnitGroup data_0854CD54[];
extern HistoryUnit data_02002FC4[];
void func_080C9644(HistoryUnit *unit, UnitSource *source, u8 mode);
u8 func_080C95A8(u16 index);
void func_08121E08(u32 value);
void func_08124CE8(void);

/* 0x081256D4: 138 bytes, including both referenced literal words. */
void func_081256D4(u16 id)
{
    UnitGroup *group = &data_0854CD54[id];
    UnitSource *source = group->sources;
    s32 i;

    for (i = 0; i < group->count; i++, source++) {
        HistoryUnit *unit = data_02002FC4;
        s32 slot;

        for (slot = 0; slot < 12; slot++, unit++) {
            if (unit->active == 0)
                break;
        }
        func_080C9644(unit, source, 0);
        if (unit->active == 0x52)
            unit->facing = 0;
    }

    if (func_080C95A8(13) == 1) {
        func_08121E08((u32)func_080C6858(data_02002FC4, 12));
    } else {
        func_08124CE8();
    }
}
