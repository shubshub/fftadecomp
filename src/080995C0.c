#include "ffta.h"

typedef struct SceneObject {
    u32 value;
    u8 unknown_04[0x3C];
    void *resource;
    void *second;
    void *first;
    u8 unknown_4C[8];
    void *handle_54;
    void *handle_58;
    u8 unknown_5C[0x24];
    void **owner;
} Object;

void func_080971F8(Object *object);
void func_0809A09C(Object *object);
void func_08021BD4(void *resource, void *attachment);
void func_08021B54(void *resource);
void func_0808F7CC(void *handle);
void func_08007170(void *owner, u8 *object);

u32 func_080995C0(Object *object)
{
    u32 value;

    func_080971F8(object);
    value = object->value;
    func_0809A09C(object);
    if (object->resource != 0) {
        if (object->first != 0)
            func_08021BD4(object->resource, object->first);
        if (object->second != 0)
            func_08021BD4(object->resource, object->second);
        func_08021B54(object->resource);
    }
    if (object->handle_54 != 0)
        func_0808F7CC(object->handle_54);
    if (object->handle_58 != 0)
        func_0808F7CC(object->handle_58);
    func_08007170(*object->owner, (u8 *)object);
    return value;
}
