#include "ffta.h"

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
    u8 unknown_00[0x10];
    const u8 *positions;
    u8 unknown_14[0x14];
} SceneDefinition;

extern SceneRecord g_state_02000080[24];
extern const SceneDefinition g_table_0854CD54[];

SceneRecord *func_08121CB4(u8 selector);
SceneRecord *func_080C83CC(u8 selector);
void *func_08096D7C(void);
SceneObject *func_08099560(void *context, SceneRecord *record);
u16 func_0800A018(void);
SceneObject *func_08124238(void);
u8 func_08124ACC(u8 x, u8 y, u8 otherX, u8 otherY);
SceneObject *func_08092440(void *context, SceneRecord *record);
void func_080CE380(SceneRecord *record, u8 enabled);
void func_08124710(SceneObject *object, u8 update, u8 value);

void func_08124560(u8 selector, u8 position)
{
    SceneRecord *record;
    SceneObject *object;

    if (selector == 0xFF) {
        SceneRecord *candidate = g_state_02000080;
        s32 index;

        record = 0;
        for (index = 0; index < 24; index++, candidate++) {
            if (candidate->flags & 0x400) {
                record = candidate;
                break;
            }
        }
    } else if ((s8)selector < 0) {
        record = func_08121CB4(selector);
    } else {
        record = func_080C83CC(selector);
    }
    object = func_08099560(func_08096D7C(), record);
    if (object == 0) {
        u32 definitionOffset = func_0800A018() * sizeof(SceneDefinition);
        const SceneDefinition *definition =
            (const SceneDefinition *)((const u8 *)g_table_0854CD54 + definitionOffset);
        const u8 *positions = definition->positions;
        s32 positionOffset = 2 * position - 2;
        const u8 *coordinates = positions + positionOffset;
        SceneObject *reference = func_08124238();

        record->x = coordinates[0];
        record->y = coordinates[1];
        record->facing = func_08124ACC(record->x, record->y,
                                     reference->record->x, reference->record->y);
        object = func_08092440(func_08096D7C(), record);
        object->record->previousX = object->record->x;
        object->record->previousY = object->record->y;
        func_080CE380(object->record, 1);
    }
    func_08124710(object, 0, 0);
}
