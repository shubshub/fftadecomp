#include "ffta.h"

// Complete target: [0x0801D938, 0x0801D980), 72 bytes, 26 instructions.

typedef struct {
    u8 unknown_00[8];
    u16 control;
    u8 unknown_0A[6];
    u32 source;
    u8 unknown_14[0x14];
    u8 buffer[0x200];
} Display0801D938;

typedef struct {
    u8 unknown_00[0x2C];
    u16 flags;
} State0801D938;

typedef void (*BufferInitializer)(void *destination, u32 size);

extern Display0801D938 data_02008168;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern void func_08141868(const void *source, void *destination, u32 control);

void func_0801D938(void)
{
    Display0801D938 *display = &data_02008168;
    u32 value = display->control;

    func_08141868(&value, (void *)display->source, 0x01001000);
    g_callbacks_0836D4B8[0](display->buffer, 0x200);
    ((State0801D938 *)((u8 *)display - 0x228))->flags |= 2;
}
