#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 height;
} RowList080601D0;

typedef struct {
    u8 unknown_00[0x3C];
    RowList080601D0 list;
} Control080601D0;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState080601D0;

typedef struct {
    u8 unknown_00[0x148];
    u8 text_state[1];
} Menu080601D0;

extern TileState080601D0 data_030008B0;
extern Menu080601D0 *data_0200F44C;
extern u16 func_08017B9C(RowList080601D0 *list, u32 index);
extern u16 func_08017B68(RowList080601D0 *list, u32 index);
extern void func_08013A88(void *destination, u32 rows);
extern const u8 *func_0805FD38(Control080601D0 *control, s16 index, u8 *flag);
extern u8 *func_0805FEA8(Control080601D0 *control, u8 *output, u16 index);
extern void func_08015110(void *state, void *tiles, const void *text, u32 style, u32 spacing);
extern void func_0805FFF0(Control080601D0 *control, u8 *buffer, u16 index);

// Complete [0x080601D0, 0x0806025C): 140 bytes, 70 instructions.
// f0b582b0061c351c3c35002201a802700c062416281c211cb7f7d8fc19490004c00a09690f18697d4900381cb3f744fc281c211cb7f7b0fc011c09040d0c0914301c01aafff790fd041c301c391c2a1cfff742fe071c0c480068a4214900401801a90b7801210091391c221cb4f768ff301c391c2a1cfff7d3fe02b0f0bc01bc0047
void func_080601D0(Control080601D0 *control, s8 row)
{
    RowList080601D0 *list = &control->list;
    u8 flag = 0;
    u8 *tiles = data_030008B0.tiles + func_08017B9C(list, row) * 32;
    u16 index;
    const u8 *text;

    func_08013A88(tiles, list->height << 1);
    index = func_08017B68(list, row);
    text = func_0805FD38(control, index, &flag);
    tiles = func_0805FEA8(control, tiles, index);
    func_08015110(data_0200F44C->text_state, tiles, text, flag, 1);
    func_0805FFF0(control, tiles, index);
}
