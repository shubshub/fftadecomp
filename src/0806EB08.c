#include "ffta.h"

typedef struct {
    u8 unknown_00[0x4BF9];
    u8 visible;
} DisplayState;

extern DisplayState *data_0200F428;
extern const u8 data_08393B00[];
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                        u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                        u32 value, u8 mode, const void *transform);

/* Complete target: [0x0806EB08, 0x0806EB48), 64 bytes, 25 instructions. */
void func_0806EB08(void)
{
    if (data_0200F428->visible)
        func_08001F34(data_08393B00, 216, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}
