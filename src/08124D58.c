#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 value_18;
    u16 value_1A;
    u16 value_1C;
    u16 value_1E;
    u8 unknown_20[8];
    u16 flags;
    u8 unknown_2A[0xAE];
    u8 first[0x10];
    u8 second[8];
    u8 unknown_F0[0x18];
} SceneRecord08124D58;

typedef struct {
    SceneRecord08124D58 *record;
    u8 unknown_04[0x1B];
    u8 value;
    u8 unknown_20[8];
    u32 field_28;
    u32 unknown_2C;
    u32 flags;
} SceneObject08124D58;

typedef void (*BufferInitializer08124D58)(void *destination, u32 size);

extern SceneRecord08124D58 g_state_02000080[24];
extern BufferInitializer08124D58 const g_callbacks_0836D4B8[];
extern SceneRecord08124D58 *func_08121CB4(u8 selector);
extern SceneRecord08124D58 *func_080C83CC(u8 category);
extern void *func_08096D7C(void);
extern SceneObject08124D58 *func_08099560(void *context,
                                        SceneRecord08124D58 *record);
extern void func_0809A304(SceneObject08124D58 *object);
extern void func_08124710(SceneObject08124D58 *object, u8 update, u8 value);

static inline SceneRecord08124D58 *findActiveRecord(void)
{
    SceneRecord08124D58 *record = g_state_02000080;
    s32 index;

    for (index = 0; index < 24; index++, record++) {
        if (record->flags & 0x400)
            return record;
    }
    return 0;
}

/* Complete [0x08124D58, 0x08124DF0): 152 bytes, 63 instructions. */
void func_08124D58(u8 selector)
{
    SceneRecord08124D58 *record;
    SceneObject08124D58 *object;

    if (selector == 0xFF)
        record = findActiveRecord();
    else if ((s8)selector < 0)
        record = func_08121CB4(selector);
    else
        record = func_080C83CC(selector);

    record->value_18 = record->value_1A;
    record->value_1C = record->value_1E;
    {
        BufferInitializer08124D58 const *callbacks = g_callbacks_0836D4B8;

        callbacks[0](record->second, sizeof(record->second));
        callbacks[0](record->first, sizeof(record->first));
    }
    object = func_08099560(func_08096D7C(), record);
    object->flags = 0;
    object->field_28 = 0;
    func_0809A304(object);
    func_08124710(object, 1, object->value);
}
