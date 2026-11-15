#include "ffta.h"

/* Complete [0x08124560, 0x08124648): 232 bytes, 101 instructions and two
 * literal words (0x02000080 at 0x08124590, 0x0854CD54 at 0x08124644). */

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2A[0xCC];
    u8 x;
    u8 y;
    u8 facing;
    u8 previousX;
    u8 previousY;
    u8 unknown_FB[0xD];
} SceneRecord;

typedef struct {
    SceneRecord *record;
} SceneObject;

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

extern SceneRecord g_state_02000080[24];
extern const SceneDefinition g_table_0854CD54[];

SceneRecord *func_08121CB4(u8 selector);
SceneRecord *func_080C83CC(u8 category);
void *func_08096D7C(void);
SceneObject *func_08099560(void *context, SceneRecord *record);
u16 func_0800A018(void);
SceneObject *func_08124238(void);
u8 func_08124ACC(u8 start_x, u8 start_y, u8 end_x, u8 end_y);
SceneObject *func_08092440(void *context, SceneRecord *record);
void func_080CE380(void *object, u8 enabled);
void func_08124710(SceneObject *object, u8 update, u8 value);

/* The selector-0xFF scan of func_08125578 (src/08125578.c), declared as in
 * src/08124480.c. */
static inline SceneRecord *findActiveRecord(void)
{
    SceneRecord *record = g_state_02000080;
    s32 index;

    for (index = 0; index < 24; index++, record++) {
        if (record->flags & 0x400)
            return record;
    }
    return 0;
}

void func_08124560(u8 selector, u8 position)
{
    SceneRecord *record;
    SceneObject *object;

    if (selector == 0xFF) {
        record = findActiveRecord();
    } else if ((s8)selector < 0) {
        record = func_08121CB4(selector);
    } else {
        record = func_080C83CC(selector);
    }
    object = func_08099560(func_08096D7C(), record);
    if (object == 0) {
        const SceneDefinition *definition = &g_table_0854CD54[func_0800A018()];
        const Position *selected = definition->origin;
        SceneObject *reference;

        selected += position - 1;
        reference = func_08124238();
        record->x = selected->x;
        record->y = selected->y;
        record->facing = func_08124ACC(record->x, record->y,
                                     reference->record->x, reference->record->y);
        object = func_08092440(func_08096D7C(), record);
        object->record->previousX = object->record->x;
        object->record->previousY = object->record->y;
        func_080CE380(object->record, 1);
    }
    func_08124710(object, 0, 0);
}
