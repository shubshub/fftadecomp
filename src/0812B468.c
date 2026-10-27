#include "ffta.h"

typedef struct State0812B468 {
    u8 unknown_000[8];
    u8 render_context[0x2F4];
    u8 *graphics;
    u8 unknown_300[8];
    u8 *text;
    u8 *workspace;
} State0812B468;

typedef void (*GraphicsInitializer0812B468)(void *destination, u32 size);

extern GraphicsInitializer0812B468 const g_callbacks_0836D4B8[];
extern const u8 data_084C3D50[];
extern u16 func_08013E9C(u8 *destination, const u8 *table, u8 *workspace,
                       u16 index, u32 first, u32 second);
extern void func_080161D4(void *source, void *destination, void *buffer,
                        u8 rows, u8 width, u8 height, u8 mode);

/* Complete [0x0812B468, 0x0812B4E0): 120 bytes, 53 instructions. */
void func_0812B468(State0812B468 *state, u8 index)
{
    u8 *graphics = state->graphics + index * 0x2100;

    g_callbacks_0836D4B8[0](graphics, 0x2100);
    func_08013E9C(state->text, data_084C3D50, state->workspace, index, 0, 0);
    func_080161D4(state->render_context, graphics, state->text, 21, 0, 0, 1);
}
