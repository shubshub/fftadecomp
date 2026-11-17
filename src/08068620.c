#include "ffta.h"

/* Complete [0x08068620, 0x0806865E): 62 bytes, 30 instructions. */

typedef struct {
    u32 callback;
    void *context;
    u8 *rows;
    u8 unknown_0C[4];
    u16 flags;
    u8 depth;
} ItemList;

typedef struct {
    u8 unknown_00[0x2C];
    ItemList list;
} ItemWindow;

typedef struct {
    u8 unknown_00[0x24];
    ItemWindow window;
} MenuState;

extern void func_0814186C(const void *source, void *destination, u32 control);

/* Zeroes the first list->depth halfwords of each of the eight 0x40-byte
 * rows at list->rows. */
void func_08068620(MenuState *state)
{
    ItemList *list = &state->window.list;
    u8 *row = list->rows;
    s32 i;

    for (i = 0; i < 8; i++) {
        /* CpuFill16(0, row, list->depth * 2): the SDK's vu16 temporary,
         * spelled through a pointer until fftadecomp-kit#164. */
        u16 zero;
        u16 *source = &zero;

        *source = 0;
        func_0814186C(source, row, list->depth | 0x01000000);
        row += 0x40;
    }
}
