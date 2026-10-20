#include "ffta.h"

typedef struct {
    u8 unknown_00[0x44];
    void *resource;
} ScriptObject;

void func_08021E28(void *resource, u32 value);

void func_0809A530(void *data, u32 value)
{
    ScriptObject *object = data;

    func_08021E28(object->resource, value);
}
