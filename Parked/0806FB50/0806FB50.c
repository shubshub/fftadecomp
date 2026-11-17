// func_0806FB50: complete [0x0806FB50, 0x0806FE14), 708 bytes.
// Target bytes:
//   f0b557464e464546e0b491b081460904090c0b9100200f904846503004884946
//   8f7e0aa86a46928f0280da313d4ad1f075fe4d463435791c0c2000900f9b0193
//   01200290281c221c3b1cbaf7e3ff780020180004000c0c90f80024182404240c
//   0d940b9803a959f0adf80006000e0e902d490b9a50014018007a1b2801d10023
//   0e930e98002800d1f6e0002188460f9a824200d394e01095b800c11901314546
//   454349190904090c7800424642430c9b9a181204120c0c200090002001900120
//   029010983b1cbaf7a5ff4146cc00684600190c30007a5bf0f5fe0006000ef900
//   c91b013149190904090c0d9b1a191204120c0423009301900020029010983b1c
//   baf788ff0b99480107494018417f880040188000054946180022012343449a46
//   43e000001a00000180d1510880005208684600190c305500b11c4919007a0b78
//   98422fd10978081c012258f069fc0006000ef11c491909785df0eafb0f904146
//   88000830784340008c304a461418251c0c35281c09490f220223baf7e9ff0f9b
//   d9798800401842000548824200d9021c201c10300321b9f723fd09e047010000
//   e7030000501c0006020e30788242bfd351460806000e80460e9a904500d26be7
//   0f9b987902281bd0022802dc012805d052e0032825d005283ad04de07c00e019
//   40004844051c9a3593214900281c0d220323baf7adff2c19004921e029010000
//   7c00e01940004844051c9a3597214900281c0d220223baf79bff2c1998214900
//   0ee07c00e01940004844051c9a350749281c0d220323baf78bff2c199c214900
//   201c0d220523baf783ff15e0350100007c00e01940004844051c9a351849281c
//   0d220323baf774ff2c19a0214900201c0d220523baf76cff0e98022817d86846
//   2a300021018068210e9a514387235b00c918494403239b1a34229a40d30fd218
//   9202d20a80235b041a43d1f037fd11b038bc9846a146aa46f0bc01bc00470000
//   3d010000

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *base;
    u8 unknown_10[0x0C];
    u16 first_tile;
    u8 unknown_1E;
    u8 tag;
} TileWindow;

typedef struct {
    u8 unknown_00[0x1A];
    u8 width;
    u8 unknown_1B[0x34 - 0x1B];
    TileWindow window;
    u8 unknown_54[0x8C - 0x54];
    u16 tiles[1];
} Panel;

typedef struct {
    u16 id;
    u16 kind;
    u8 sources[4];
} GrantedAbility;

typedef struct {
    u16 count;
    u16 unknown_02;
    GrantedAbility entries[3];
} GrantedAbilities;

typedef struct {
    u8 count;
    u8 unknown_01;
    u8 entries[9][2];
} ItemAbilities;

typedef struct {
    u8 unknown_00[8];
    u8 kind;
    u8 unknown_09[0x1D - 0x09];
    u8 abilities;
    u8 unknown_1E[2];
} ItemRecord;

typedef struct {
    u8 unknown_00[6];
    u8 type;
    u8 cost;
} AbilityInfo;

extern const ItemRecord g_table_0851D180[];
extern const ItemAbilities g_table_08520080[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0802AB64(TileWindow *state, u16 index, u16 value, u8 offset,
    u8 count, u16 tag, u8 flag);
extern u8 func_080C8D14(u16 item, GrantedAbilities *out);
extern u32 func_080CBA14(u8 value);
extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern const AbilityInfo *func_080CD480(u8 kind, u8 ability);
extern void func_0802ACA0(u16 *destination, u16 tile, u8 palette, u16 count);
extern void func_08029730(u16 *destination, u8 digits, u16 value);

void func_0806FB50(Panel *panel, u16 item)
{
    u16 base;
    u8 width;
    u16 clear;
    u16 row_value;
    u16 icon_value;
    u8 count;
    const AbilityInfo *info;
    GrantedAbilities granted;
    u8 i;
    u8 j;
    const ItemAbilities *table;
    u16 *row;
    u16 *p;
    u32 cost;

    info = 0;
    base = panel->window.first_tile;
    width = panel->width;
    clear = 0;
    func_0814186C(&clear, &panel->tiles[39], 0x0100001A);
    func_0802AB64(&panel->window, width + 1, base, width, 12, 0, 1);
    row_value = base + width * 2;
    icon_value = base + width * 8;
    count = func_080C8D14(item, &granted);
    if (g_table_0851D180[item].kind == 0x1B)
        count = 0;
    if (count != 0) {
        for (i = 0; i < count; i++) {
            func_0802AB64(&panel->window, width * 5 + 1 + i * 4 * width,
                row_value + i * 2 * width, width, 12, 0, 1);
            func_0802AB64(&panel->window, width * 7 + 1 + i * 4 * width,
                icon_value + i * 8, width, 4,
                (u8)func_080CBA14(granted.entries[i].sources[0]), 0);
            table = &g_table_08520080[(g_table_0851D180 + item)->abilities];
            for (j = 0; j < table->count; j++) {
                if (granted.entries[i].sources[0] == table->entries[j][0]) {
                    info = func_080CD480(
                        func_080C8570(table->entries[j][0], table->entries[j][0], 1),
                        table->entries[j][1]);
                    row = &panel->tiles[(i * 4 + 8) * width];
                    p = row + 6;
                    func_0802ACA0(p, 0x147, 15, 2);
                    cost = info->cost * 10;
                    if (cost > 999)
                        cost = 999;
                    func_08029730(row + 8, 3, cost);
                    break;
                }
            }
        }
        switch (info->type) {
        case 1:
            p = &panel->tiles[width * 3] + 7;
            func_0802ACA0(p, 0x126, 13, 3);
            func_0802ACA0(p + width, 0x129, 13, 5);
            break;
        case 2:
            p = &panel->tiles[width * 3] + 7;
            func_0802ACA0(p, 0x12E, 13, 2);
            func_0802ACA0(p + width, 0x130, 13, 5);
            break;
        case 3:
            p = &panel->tiles[width * 3] + 7;
            func_0802ACA0(p, 0x135, 13, 3);
            func_0802ACA0(p + width, 0x138, 13, 5);
            break;
        case 5:
            p = &panel->tiles[width * 3] + 7;
            func_0802ACA0(p, 0x13D, 13, 3);
            func_0802ACA0(p + width, 0x140, 13, 5);
            break;
        }
    }
    if (count < 3) {
        u16 zero = 0;

        func_0814186C(&zero, &panel->tiles[65 + count * 52],
            0x01000000 | (((0x34 << (3 - count)) / 2) & 0x1FFFFF));
    }
}
