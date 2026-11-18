#include "history_unit.h"

typedef struct {
    u8 fields[0x30];
} UnitDefinition;

typedef struct {
    u8 x;
    u8 y;
} __attribute__((packed)) Position;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    UnitDefinition *units;
    u8 unknown_08[5];
    u8 positionCount;
    u8 unknown_0E[2];
    const Position *origin;
    const Position *positions;
    u8 unknown_18[0x10];
} SceneDefinition;

extern const SceneDefinition g_table_0854CD54[];
extern HistoryUnit g_state_02002FC4[];
u32 func_08002804(void);
void func_080C9644(void *destination, void *source, u8 levelOverride);
u8 func_08124ACC(u8 x, u8 y, u8 originX, u8 originY);
u8 func_080C95A8(u16 selector);
void func_08121E08(u32 value);
void func_08124CE8(void);

static inline u8 chooseUnusedPosition(u16 *usedPositions, u8 count)
{
    u8 position;
    u16 previousPositions = *usedPositions;

    do {
        position = (s16)func_08002804() % count;
    } while ((previousPositions >> position) & 1);
    *usedPositions |= 1 << position;
    return position;
}

void func_08124BB4(u16 unitSelector, u16 positionSelector)
{
    u16 usedPositions = 0;
    const SceneDefinition *units = &g_table_0854CD54[unitSelector];
    const SceneDefinition *layout = &g_table_0854CD54[positionSelector];
    UnitDefinition *definition = units->units;
    const Position *origin = layout->origin;
    s32 count = 0;

    for (; count < units->count; definition++) {
        HistoryUnit *record = g_state_02002FC4;
        s32 index = 0;
        u8 position;
        u8 positionCount;
        const Position *selected;
        while (index < 12 && record->active) {
            index++;
            record++;
        }
        func_080C9644(record, definition, 0);
        count++;
        positionCount = layout->positionCount;
        position = chooseUnusedPosition(&usedPositions, positionCount);
        selected = layout->positions;
        selected += position;
        record->x = selected->x;
        record->y = selected->y;
        if (record->active == 0x52)
            record->facing = 0;
        else
            record->facing = func_08124ACC(record->x, record->y, origin->x, origin->y);
    }
    if (func_080C95A8(13) == 1)
        func_08121E08((u32)func_080C6858(g_state_02002FC4, 12));
    else
        func_08124CE8();
}
