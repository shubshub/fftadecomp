#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2fba];
    u8 page;
    u8 number;
} NumberDisplay;

extern NumberDisplay g_state_02000000;
extern u8 *g_state_03002810;
extern u8 data_02003CB0[];
extern const u8 data_083ACD68[];
extern const u8 data_0839195A[];
extern u8 data_06010BC0[];
extern u8 data_06010DC0[];
extern u8 data_06010E00[];
extern u8 data_06010DE0[];
extern u8 data_06010E20[];

extern s32 func_08005318(const void *archive, u8 *output, u16 first, u16 count);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08035CAC(u8 *output, u16 value);
extern u16 func_08015110(void *context, void *tiles, const u8 *text, u8 style, u8 spacing);
extern u32 func_0808A604(u32 renderer, u16 command);

void func_08035D00(s32 refresh)
{
    u8 *buffer = data_02003CB0;
    u8 *tiles = data_02003CB0 + 0x100;

    func_08005318(data_083ACD68, buffer,
        data_0839195A[(g_state_02000000.page - 1) % 6] >> 1, 12);
    func_0814186C(buffer, data_06010BC0, 0x100);
    func_08035CAC(buffer, g_state_02000000.number);
    func_08015110(g_state_03002810 + 0xc4c, tiles, buffer, 0, 1);
    if (g_state_02000000.number < 10) {
        u32 clear = 0;
        func_0814186C(&clear, tiles, 0x05000010);
        tiles += 4;
    }
    func_0814186C(tiles, data_06010DC0, 0x10);
    func_0814186C(tiles + 0x20, data_06010E00, 0x10);
    func_0814186C(tiles + 0x40, data_06010DE0, 0x10);
    func_0814186C(tiles + 0x60, data_06010E20, 0x10);
    if (refresh == 1)
        func_0808A604(3, 2);
}
