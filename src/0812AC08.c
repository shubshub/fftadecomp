#include "ffta.h"

/* 0x0812AC08..0x0812AD14: 268 bytes. */
typedef struct {
    u8 unknown_00[4];
    u16 pressed;
} InputState;

typedef struct {
    u8 unknown_00[0x2F6];
    s8 page;
    u8 unknown_2F7[5];
    void *contents;
} PageMenu;

extern InputState data_03000000;
extern u8 data_0600A280[];
extern u8 data_06016300[];
extern const u8 data_083A82E4[];
extern const u8 data_083A82DC[];

extern void func_080023D0(InputState *input);
extern void func_08141540(u32 sound);
extern void *func_0812B4E0(PageMenu *menu);
extern void func_0812B44C(void *view, void *contents, void *destination, u8 page);
extern void func_0812B41C(void *view, void *destination, u8 page);
extern void func_08001F34(const void *image, u32 x, u32 y, u32 a3,
                        u32 a4, u32 a5, u32 a6, u32 a7, u32 a8,
                        u32 a9, u32 a10);

void func_0812AC08(PageMenu *menu)
{
    if (data_03000000.pressed & 0x100) {
        func_080023D0(&data_03000000);
        func_08141540(0x66);
        if (++menu->page > 1)
            menu->page = 0;
        func_0812B44C(func_0812B4E0(menu), menu->contents,
                      data_0600A280, (u8)menu->page);
        func_0812B41C(func_0812B4E0(menu), data_06016300,
                      (u8)menu->page);
    } else if (data_03000000.pressed & 0x200) {
        func_080023D0(&data_03000000);
        func_08141540(0x66);
        if (--menu->page < 0)
            menu->page = 1;
        func_0812B44C(func_0812B4E0(menu), menu->contents,
                      data_0600A280, (u8)menu->page);
        func_0812B41C(func_0812B4E0(menu), data_06016300,
                      (u8)menu->page);
    }
    func_08001F34(data_083A82E4, 0x18, 3, 0, 0, 0, 0, 0, 0, 0, 0);
    func_08001F34(data_083A82DC, 0x98, 3, 0, 0, 0, 0, 0, 0, 0, 0);
}
