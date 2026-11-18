#include "ffta.h"

typedef struct {
    u8 unknown_00[2];
    u8 defaultValue;
    u8 unknown_03[0x25];
} SceneDefinition;

extern const SceneDefinition g_table_0854CD54[];
extern u8 g_state_0200F390;
extern u16 func_0800A018(void);
extern void func_080C95C0(u16 index, u32 value);

u32 func_08122D20(void *state, const u8 *command)
{
    if (command[1] == 0) {
        u16 index = func_0800A018();
        const SceneDefinition *scene = &g_table_0854CD54[index];

        func_080C95C0(7, scene->defaultValue);
    } else {
        func_080C95C0(7, command[1]);
    }
    g_state_0200F390 = 10;
    return 0x112;
}
