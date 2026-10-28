#include "ffta.h"

typedef struct {
    u8 unknown_000[0x68c];
    u8 text_state[0];
} MenuContext08089AAC;

extern MenuContext08089AAC *data_03002818;
extern void func_08013A88(void *destination, u16 count);
extern void func_08015110(void *context, void *destination, const u8 *text,
                         u32 mode, u32 spacing);

/* Complete target [0x08089AAC, 0x08089B0C): 96 bytes, 36 instructions. */
void func_08089AAC(void *destination, const u8 *text, u16 count, u32 mode)
{
    func_08013A88(destination, count * 2);
    if (mode == 0)
        func_08015110(data_03002818->text_state, destination, text, 0, 1);
    else
        func_08015110(data_03002818->text_state, destination, text, 1, 1);
}
