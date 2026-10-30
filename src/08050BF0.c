/* Target bytes (72):
 * 30 b5 04 1c 09 06 09 0e 0d 1c 20 7a 04 28 0f d1
 * 20 1c 48 30 09 06 09 16 c6 f7 ae ff 00 04 21 68
 * 80 0b 08 4a 89 18 09 18 08 68 40 88 00 28 06 d1
 * 20 1c 48 30 29 06 09 16 ff 22 c6 f7 63 ff 30 bc
 * 01 bc 00 47 24 04 00 00
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[3];
    u8 field_15;
    u8 unknown_16[2];
    u16 field_18;
    u16 field_1A;
} Window08050BF0;

typedef struct {
    u16 unknown_00;
    u16 field_02;
} Entry08050BF0;

typedef struct {
    u8 unknown_000[0x424];
    Entry08050BF0 *entries[0];
} Root08050BF0;

typedef struct {
    Root08050BF0 *root;
    u8 unknown_04[4];
    u8 mode;
    u8 unknown_09[0x3F];
    Window08050BF0 window;
} Context08050BF0;

extern u16 func_08017B68(Window08050BF0 *window, u32 index);
extern void func_08017AF4(Window08050BF0 *window, s8 index, u32 value);

void func_08050BF0(Context08050BF0 *context, u8 index)
{
    if (context->mode == 4) {
        u16 selected = func_08017B68(&context->window, (s8)index);

        if (context->root->entries[selected]->field_02 != 0)
            return;
    }

    func_08017AF4(&context->window, (s8)index, 0xFF);
}
