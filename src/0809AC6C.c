#include "ffta.h"

typedef struct Collection Collection;

typedef struct {
    s32 key;
    void *value;
} CollectionEntry;

typedef struct {
    u8 unknown_00[0x24];
    s32 key;
} SceneObject;

CollectionEntry *func_080C7C14(Collection *collection, SceneObject *object);
void func_080C7C40(CollectionEntry *entry, void *value, s32 key);

s32 func_0809AC6C(SceneObject *object, Collection *collection)
{
    CollectionEntry *entry = func_080C7C14(collection, object);

    func_080C7C40(entry, object, object->key);
    return 1;
}
