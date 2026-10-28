#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u8 state;
} SceneState;

void func_08022BA4(u32 first, u32 second);

void func_0809A624(SceneState *scene)
{
    func_08022BA4(1, 2);
    scene->state = 0;
}
