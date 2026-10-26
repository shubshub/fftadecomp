#include "ffta.h"

/* 0x0806FFAC..0x0806FFE4: 56 bytes. */
typedef struct {
    u8 unknown_00[0x10];
    u8 *buffer;
} TextSurface;

typedef struct {
    u8 unknown_00[0x7C];
    void *text_state;
} MenuContext;

extern TextSurface data_030008B0;
extern void func_08013A88(u8 *buffer, u32 length);
extern void func_08015110(void *state, u8 *buffer, const u8 *source,
                          u32 mode, u32 enabled);

void func_0806FFAC(MenuContext *context, const u8 *source, u16 index)
{
    u8 *buffer = data_030008B0.buffer + index * 0x20;

    func_08013A88(buffer, 0x18);
    func_08015110(context->text_state, buffer, source, 5, 1);
}
