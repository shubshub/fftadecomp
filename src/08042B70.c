#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    const void *text;
    u8 unknown_0c[8];
} TextEntry08042B70;

typedef struct {
    u8 unknown_00[0x18];
    TextEntry08042B70 *entries;
} Menu08042B70;

typedef struct {
    u8 unknown_000[0xc4c];
    u8 text[1];
} Global08042B70;

extern u8 data_02003CB0[];
extern Global08042B70 *g_state_03002810;
extern void func_080CB980(void *, u32);
extern void func_080CB9B0(void *, u32);
extern void func_0814186C(const void *, void *, u32);
extern void func_08015110(void *, void *, const void *, u32, u32);

/* Complete [0x08042B70, 0x08042C10): 160 bytes, 65 instructions. */
void func_08042B70(u16 id, u16 index, u8 *tiles, Menu08042B70 *menu,
                   u32 unused, u8 type, u32 selected)
{
    const void *text = data_02003CB0;

    if (type == 0)
        func_080CB980((void *)text, id);
    else if (type == 1)
        func_080CB9B0((void *)text, (u8)id);

    func_0814186C(text, tiles, 0x40);
    text = menu->entries[index].text;
    if (selected)
        func_08015110(g_state_03002810->text, tiles + 0x80, text, 0, 1);
    else
        func_08015110(g_state_03002810->text, tiles + 0x80, text, 1, 1);
}
