#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
} InitializationEntry;

typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x103];
} SceneRecord;

typedef struct {
    u8 unknown_00[0xF6];
    u8 status_a;
    u8 status_b;
    u8 unknown_F8;
    u8 previous_status_a;
    u8 previous_status_b;
} ObjectData;

typedef struct {
    ObjectData *data;
} SceneObject;

extern const InitializationEntry g_table_0854CD54[];
extern SceneRecord g_state_02002FC4[];

s32 func_080CA744(const InitializationEntry *entry, SceneRecord *records,
                 s32 maximum);
SceneObject *func_08092440(void *context, SceneRecord *record);

void func_08096E18(u16 index, void *context)
{
    SceneRecord *record;
    s32 remaining;

    func_080CA744(&g_table_0854CD54[index], g_state_02002FC4, 12);
    record = g_state_02002FC4;
    for (remaining = 11; remaining >= 0; remaining--, record++) {
        if (record->active != 0) {
            SceneObject *object = func_08092440(context, record);

            object->data->previous_status_a = object->data->status_a;
            object->data->previous_status_b = object->data->status_b;
        }
    }
}
