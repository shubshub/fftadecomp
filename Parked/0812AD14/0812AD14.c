#include "ffta.h"

/* 0812AD14 .. 0812ADDC: 200 bytes. */
typedef struct {
    u8 cells[60][2];
} TextPage;

typedef struct {
    u8 unknown_000[0x304];
    TextPage *pages;
    u8 *buffer;
    const void *source;
} TextState;

extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern const u8 data_084C3D50[];
extern void func_08013E9C(u8 *, const u8 *, const void *, s32, s32, s32);

void func_0812AD14(TextState *state, u8 page)
{
    u8 (*cells)[2] = state->pages[page].cells;
    s32 column;
    s32 position;
    s32 row;

    g_callbacks_0836D4B8[0](cells, sizeof(TextPage));
    g_callbacks_0836D4B8[0](state->buffer, 0x100);
    func_08013E9C(state->buffer, data_084C3D50, state->source, page, 0, 0);
    column = 0;
    position = 0;
    row = 0;
    for (;;) {
        u32 first = state->buffer[position];
        if (first == '@') {
            u8 command = state->buffer[++position];
            switch (command) {
            case 'n':
                column = 0;
                row += 10;
                position++;
                break;
            case 's':
                cells[row + column][0] = first;
                cells[row + column][1] = command;
                column++;
                position++;
                break;
            case '>':
                position += 2;
                break;
            case 'c':
                return;
            }
        } else {
            cells[row + column][0] = first;
            cells[row + column][1] = state->buffer[position + 1];
            column++;
            position += 2;
        }
    }
}
