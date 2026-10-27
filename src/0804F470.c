#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 frame;
    u8 unknown_0A[4];
    s16 timer;
} Animation;

typedef struct {
    u8 unknown_00[9];
    u8 enabled;
    u8 unknown_0A[2];
    Animation first;
    Animation second;
} AnimatedObject;

typedef struct {
    u8 unknown_00[0x12];
    u8 mode;
} SceneState;

extern SceneState g_state_020020D0;
extern void func_08017FE8(Animation *animation);

/* Complete target: 0x0804F470..0x0804F4D4, 100 bytes. */
void func_0804F470(AnimatedObject *object)
{
    if (object->enabled && g_state_020020D0.mode != 3)
    {
        object->first.timer++;
        if (object->first.timer > 5)
        {
            object->first.timer = 0;
            object->first.frame++;
            if (object->first.frame > 2)
                object->first.frame = 0;
            object->second.frame--;
            if (object->second.frame <= -3)
                object->second.frame = 0;
        }
        func_08017FE8(&object->first);
        func_08017FE8(&object->second);
    }
}
