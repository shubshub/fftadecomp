#include "ffta.h"

// Complete target [0x08082924,0x08082AEC), 456 bytes:
// f0b557464e464546e0b481b082460091504f3d68cc205446444328194e4940180688009a002a19d1
// 60194c4bc0184c4aa918091909684b4b4c227243d218d289494eab191b191b681b8893f74ffc3868
// 2018b42189014018fef7f0ff38680219424bd21813880221194311802018b426b601801995f7daf8
// 0004060c0025b5420edab8463a4827182904091443461a68d21978325046fef77bfd0135b542f3db
// 2c480168cc2056464643301c0918314a881800884004b4239b01cc18050c201c95f7b4f84004667d
// b046a768060c002e1bd0c146e17d4900281cbff0a7ff0004050c414669434900e0684018391c4a46
// 214b1a40bef028ffa07f40003f18013e681c0004050c002ee4d1009e002e4dd110480168cc205446
// 4443134a881800190068006800282ddd64180c4be418134a134e251c2c35201c4c30291c002395f7
// e1f86034201c291c321c0d2395f7a0f92ce0000018280003b82c0000d42c0000482d0000e0090003
// d02c0000102d0000882c00001a2d0000ffff1f00791008088d11080864180d4ea4190d4a0d4e251c
// 2c35201c4c30291c002395f7b3f86034201c291c321c0d2395f772f901b038bc9846a146aa46f0bc
// 01bc0047d42c0000795308088d110808

typedef struct {
    u8 unknown_00[8];
    u16 *unknown_08;
    u16 *unknown_0C;
    u16 unknown_10;
    u8 unknown_12[3];
    u8 unknown_15;
    u8 unknown_16;
    u8 unknown_17;
    s16 unknown_18;
    u16 unknown_1A;
    u16 unknown_1C;
    u8 unknown_1E;
    u8 unknown_1F;
} Menu08082924;

typedef struct {
    u8 panel[0x2C];
    Menu08082924 menu;
    u8 cursor[0x14];
    u8 settings[0x14];
} Window08082924;

typedef struct {
    u8 unknown_00[0x30];
    u16 unknown_30;
    u8 unknown_32[0x16];
    s32 *unknown_48;
    Window08082924 window;
    void *unknown_C0;
    u8 unknown_C4[8];
} Slot08082924;

typedef struct {
    u8 unknown_0000[0x2C88];
    Slot08082924 slots[0];
} State08082924;

typedef struct {
    u8 unknown_00[0xE];
    u16 unknown_0E;
    u8 unknown_10[0x3C];
} Layer08082924;

extern State08082924 *data_03002818;
extern Layer08082924 data_030009E0[];
extern void func_08016210(void *object, const void *content, u16 first, u16 second);
extern void func_08081960(Menu08082924 *menu);
extern u16 func_08017B50(Menu08082924 *menu);
extern void func_080814B4(s32 index, s16 row, Menu08082924 *menu);
extern s32 func_08142950(s32 value, s32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 count);
extern void func_08017C28(void *cursor, Menu08082924 *menu, void (*callback)(), u32 mode);
extern void func_08017DB4(void *settings, Menu08082924 *menu, void (*callback)(), u32 mode);
extern void func_08081078();
extern void func_0808118C();
extern void func_08085378();

static inline void func_08082924_reset(Menu08082924 *menu)
{
    func_08081960(menu);
}

static inline void func_08082924_copy(Menu08082924 *menu, u16 frame)
{
    u16 line_count = func_08017B50(menu) * 2;
    u32 width = menu->unknown_15;
    u16 *destination = menu->unknown_08;
    s32 remaining = line_count;
    u32 transfer_count;

    if (remaining != 0) {
        transfer_count = width;
        do {
            frame = func_08142950(frame, menu->unknown_17 * 2);
            func_0814186C(menu->unknown_0C + frame * width,
                          destination, transfer_count & 0x1FFFFF);
            destination += menu->unknown_1E;
            remaining--;
            frame++;
        } while (remaining != 0);
    }
}

static inline void func_08082924_attach(Window08082924 *window, void (*callback)(), void (*handler)())
{
    Menu08082924 *menu = &window->menu;

    func_08017C28(window->cursor, menu, callback, 0);
    func_08017DB4(window->settings, menu, handler, 13);
}

void func_08082924(s32 index, u32 refresh)
{
    u16 layer = data_03002818->slots[index].unknown_30;
    s32 i;
    u16 count;

    if (refresh == 0) {
        func_08016210(data_03002818->slots[index].window.panel,
                      data_03002818->slots[index].unknown_C0,
                      data_030009E0[layer].unknown_0E,
                      *data_03002818->slots[index].unknown_48);
        func_08082924_reset(&data_03002818->slots[index].window.menu);
    }

    data_03002818->slots[index].window.menu.unknown_10 |= 2;
    count = func_08017B50(&data_03002818->slots[index].window.menu);
    for (i = 0; i < count; i++)
        func_080814B4(index, i, &data_03002818->slots[index].window.menu);

    func_08082924_copy(&data_03002818->slots[index].window.menu,
                       data_03002818->slots[index].window.menu.unknown_1A * 2);

    if (refresh == 0) {
        if (*data_03002818->slots[index].unknown_48 > 0)
            func_08082924_attach(&data_03002818->slots[index].window, func_08081078, func_0808118C);
        else
            func_08082924_attach(&data_03002818->slots[index].window, func_08085378, func_0808118C);
    }
}
