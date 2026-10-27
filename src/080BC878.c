#include "ffta.h"

typedef struct {
    u8 unknown_00[0x74];
    void *owner;
} Object080BC878;

extern Object080BC878 data_02010130;
extern void (*g_callbacks_0836D4B8[])(void *object, u32 size);
extern void func_080BB5C4(void *object, void *configuration, u8 first, u8 second);

/* 0x080BC878: 76 bytes; initialize and configure the global owned object. */
void func_080BC878(void *owner, void *configuration, u8 first, u8 second)
{
    g_callbacks_0836D4B8[0](&data_02010130, 0xC0);
    func_080BB5C4(&data_02010130, configuration, first, second);
    data_02010130.owner = owner;
}
