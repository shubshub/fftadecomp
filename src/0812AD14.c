#include "ffta.h"

typedef struct {
    u8 cells[60][2];
} TextPage;

typedef struct {
    u8 unknown_000[0x304];
    TextPage *characters;
    u8 *text;
    u8 *workspace;
} TextState;

extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern const u8 data_084C3D50[];
extern u16 func_08013E9C(u8 *destination, const u8 *table, u8 *workspace,
                         u16 index, u8 *status, u8 *mode);

/* Complete [0x0812AD14, 0x0812ADDC): 200 bytes, 93 instructions. */
void func_0812AD14(TextState *state, u8 page)
{
    u8 (*cells)[2] = state->characters[page].cells;
    s32 column;
    s32 position;
    s32 line;

    g_callbacks_0836D4B8[0](cells, sizeof(TextPage));
    g_callbacks_0836D4B8[0](state->text, 0x100);
    func_08013E9C(state->text, data_084C3D50, state->workspace, page, 0, 0);
    column = 0;
    position = 0;
    line = 0;
    for (;;) {
        if (state->text[position] == '@') {
            position++;
            switch (state->text[position]) {
            case 'n':
                column = 0;
                line++;
                position++;
                break;
            case 's':
                cells[line * 10 + column][0] = '@';
                cells[line * 10 + column][1] = 's';
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
            cells[line * 10 + column][0] = state->text[position];
            cells[line * 10 + column][1] = state->text[position + 1];
            column++;
            position += 2;
        }
    }
}
