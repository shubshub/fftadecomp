#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *primary;
    u8 unknown_08[12];
    u16 x;
    u16 y;
    u16 variant;
} Descriptor080EEE50;

typedef u32 (*Callback080EEE50)(void *task, Descriptor080EEE50 *descriptor,
                              void *payload);

extern void func_080D8B5C(void *object, s16 *x, s16 *y);
extern u8 func_0801CC18(u8 x, u8 y);
extern void func_0801CA78(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output,
                         s16 *third_output);
extern void func_0801C984(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output);
extern u32 func_080EED88(void *task, Descriptor080EEE50 *descriptor,
                        void *payload);
extern void *func_08005B6C(Callback080EEE50 callback, u16 payload_size,
                          Descriptor080EEE50 *descriptor, void *parent);

/* Complete target: 160 bytes. The descriptor follows the actual callback's
 * observed members and remains partially initialized exactly as in the root.
 * Helper signatures describe conditional incoming transport; they do not
 * assert memory effects, initialization, bounds or termination. */
void *func_080EEE50(void *object, u8 variant, void *parent)
{
    Descriptor080EEE50 descriptor;
    s16 tile_x, tile_y;
    s16 world_x, world_y, world_z;
    s16 screen_x, screen_y;
    u8 height;

    func_080D8B5C(object, &tile_x, &tile_y);
    height = func_0801CC18(tile_x, tile_y);
    func_0801CA78(tile_x, height, tile_y, &world_x, &world_y, &world_z);
    func_0801C984(world_x, world_y, world_z, &screen_x, &screen_y);
    descriptor.x = screen_x;
    descriptor.y = screen_y;
    descriptor.variant = variant;
    descriptor.primary = object;
    return func_08005B6C(func_080EED88, 0x1C, &descriptor, parent);
}
