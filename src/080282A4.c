#include "ffta.h"

typedef struct BlockLayout080282A4 {
    u8 unknown_00[8];
    u8 appearance;
    u8 unknown_09[3];
    u16 counts;
} BlockLayout080282A4;

typedef struct Window080282A4 {
    u8 unknown_00[0x0C];
    u8 window[0x74];
    BlockLayout080282A4 layout;
} Window080282A4;

typedef struct BlockResources080282A4 {
    u8 unknown_00[0x2C4];
    u8 blocks[0x180];
} BlockResources080282A4;

extern const BlockResources080282A4 *data_0200F438;
extern void func_08013B7C(const BlockLayout080282A4 *layout,
                          void *destination, const u8 *source);
extern void func_08016C90(void *window, u8 appearance);

/* Complete [0x080282A4, 0x080282D4): 48 bytes, 19 instructions. */
void func_080282A4(Window080282A4 *state)
{
    void *window = state->window;
    const BlockLayout080282A4 *layout = &state->layout;

    func_08013B7C(layout, window, data_0200F438->blocks);
    func_08016C90(window, layout->appearance);
}
