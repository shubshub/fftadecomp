#include "ffta.h"

typedef struct {
    void *record;
} SceneObject;

s32 func_08131BE0(void *record, s8 x, s8 y);

s32 func_08099C1C(void *object, s8 x, s8 y)
{
    SceneObject *sceneObject = object;

    return func_08131BE0(sceneObject->record, x, y);
}
