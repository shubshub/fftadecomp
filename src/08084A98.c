#include "ffta.h"

// Complete target [0x08084A98,0x08084BD0), 312 bytes:
// f0b54f464646c0b482b0051c0904090c884613480268cc20291c4143114bd01840180068814652180f49501801880f4b
// 4c204843c0184a300078000600160004070cb4239b01d418414608060016628b80180204111400290ada002011e00000
// 18280003502d0000b82c0000e00900031823e05e0138814202dd208b013800e0100c0004000ce17dbdf016ff0004000c
// 79004843a48b001900041b4e3168cc222c1c5443194a89180919c00a09680d18002001903a0180204004024301a8291c
// bcf086fe30682418b4239b01e418404601060916201c92f7fbff0004000c49468a6981000918890089188a6848880028
// 10d13068064bc01801210091291c012390f7bafa0fe0000018280003982c00008c06000030680749401801210091291c
// 002390f7a9fa02b018bc9846a146f0bc01bc00478c060000

typedef struct {
    u8 unknown_00[0x17];
    u8 unknown_17;
    u16 unknown_18;
    u16 unknown_1A;
    u16 unknown_1C;
    u8 unknown_1E[2];
} Menu08084A98;

typedef struct {
    u8 unknown_00[2];
    u16 unknown_02;
    u8 unknown_04[4];
    const u8 *unknown_08;
    u8 unknown_0C[8];
} Entry08084A98;

typedef struct {
    u8 unknown_00[0x18];
    Entry08084A98 *unknown_18;
} Object08084A98;

typedef struct {
    u8 unknown_00[0x10];
    u8 *unknown_10;
    u8 unknown_14[0x1C];
    u16 unknown_30;
    u8 unknown_32[0x46];
    Menu08084A98 menu;
    u8 unknown_98[0x30];
    Object08084A98 *unknown_C8;
} Slot08084A98;

typedef struct {
    u8 unknown_0000[0x68C];
    u8 text[0x25FC];
    Slot08084A98 slots[0];
} State08084A98;

typedef struct {
    u8 unknown_00[0x4A];
    s8 unknown_4A;
    u8 unknown_4B;
} Layer08084A98;

extern State08084A98 *data_03002818;
extern Layer08084A98 data_030009E0[];
extern s32 func_08142950(s32 value, s32 divisor);
extern void func_08141868(const void *source, void *destination, u32 control);
extern u16 func_08017B68(Menu08084A98 *menu, u32 row);
extern void func_08015110(void *context, void *destination, const u8 *text, u32 mode, u32 reset);

void func_08084A98(s32 index, u16 row)
{
    Object08084A98 *object = data_03002818->slots[index].unknown_C8;
    u16 layer = data_03002818->slots[index].unknown_30;
    u16 width = data_030009E0[layer].unknown_4A;
    Menu08084A98 *menu = (Menu08084A98 *)(index * sizeof(Slot08084A98) + (u32)data_03002818 + 0x2D00);
    s16 position = (s8)row + menu->unknown_1A;
    s32 line;
    u16 tile;
    s32 size;
    u16 frame;
    u16 selected;
    u8 *destination;
    u32 zero;
    const u8 *text;

    if (position < 0)
        line = 0;
    else if (position > (s16)menu->unknown_18 - 1)
        line = menu->unknown_18 - 1;
    else
        line = (u16)position;

    /* Called by name: written as %, agbcc keeps &data_03002818 in a callee-saved
       register across the call, where the ROM reloads it afterwards. */
    frame = func_08142950((u16)line, menu->unknown_17);
    size = width * 2;
    tile = frame * size + menu->unknown_1C;
    destination = data_03002818->slots[index].unknown_10 + tile * 32;
    zero = 0;
    func_08141868(&zero, destination, ((u32)size << 3) | 0x01000000);

    selected = func_08017B68(&data_03002818->slots[index].menu, (s8)row);
    text = object->unknown_18[selected].unknown_08;
    if (object->unknown_18[selected].unknown_02 == 0)
        func_08015110(data_03002818->text, destination, text, 1, 1);
    else
        func_08015110(data_03002818->text, destination, text, 0, 1);
}
