#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
} Animation;

typedef struct {
    u8 unknown_00[0xC];
    Animation first;
    Animation second;
    void *window;
} MenuObject;

typedef struct {
    u8 unknown_00[0x10];
    u8 selection;
} SceneState;

extern SceneState g_state_020020D0;
extern u8 data_030008B0[];
extern u8 data_03000990[];
extern const u8 data_0851BA72[];
extern const u8 data_0851BA7A[];
extern void func_0801174C(void *window, s32 id, u8 selection,
                          void *first, void *second, s32 index, u32 flags,
                          u32 width, u32 height, u32 tile);
extern void func_08017FA8(Animation *animation, const u8 *graphics, s16 x, s16 y);

/* Complete target: 0x08050E94..0x08050EFC, 104 bytes. */
void func_08050E94(MenuObject *object)
{
    func_0801174C(object->window, 9, g_state_020020D0.selection,
                  data_030008B0, data_03000990, 2, 1, 24, 16, 0x140);
    func_08017FA8(&object->first, data_0851BA72, 216, 14);
    func_08017FA8(&object->second, data_0851BA7A, 24, 14);
}
