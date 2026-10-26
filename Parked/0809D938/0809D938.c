#include "ffta.h"

typedef struct {
    void *object;
    u8 unknown_04[0xB0];
} SceneEntry;

typedef struct {
    u8 unknown_00[0xC];
    SceneEntry entries[13];
} SceneContainer;

void func_08022854(void *object);

void func_0809D938(SceneContainer *container)
{
    s32 index;

    for (index = 0; index <= 12; index++) {
        SceneEntry *entry = &container->entries[index];

        if (entry->object != 0) {
            func_08022854(entry->object);
            entry->object = 0;
        }
    }
    func_08022854(container);
}
