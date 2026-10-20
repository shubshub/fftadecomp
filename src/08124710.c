#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 category;
    u8 unknown_05[2];
    u8 kind;
    u8 unknown_08[0xF0];
    u8 value;
} SceneRecord;

typedef struct {
    SceneRecord *record;
} SceneObject;

void func_0809836C(SceneObject *object, u16 action, s8 value, u16 option);
void func_0809A530(SceneObject *object, u32 value);
void func_0809A570(SceneObject *object, u16 clear, u16 set);

void func_08124710(SceneObject *object, u8 update, u8 value)
{
    SceneRecord *record = object->record;

    if (record->kind == 0x31 || record->kind == 0x32 ||
        record->kind == 0x45 || record->kind == 0x46 ||
        record->kind == 0x47 || record->category == 0x1E ||
        record->category == 0x39 || record->category == 0x3A ||
        record->category == 0x3B || record->category == 0x3C ||
        record->category == 0x3D || record->category == 0x3E ||
        record->category == 0x3F) {
        if (update) {
            func_0809836C(object, 0, (s8)value, 0);
            object->record->value = value;
        }
        func_0809A570(object, 0, 2);
    } else {
        if (update) {
            func_0809836C(object, 0, (s8)value, 0);
            object->record->value = value;
        }
        func_0809A530(object, 1);
        func_0809A570(object, 0, 0x100);
    }
}
