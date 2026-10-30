#include "ffta.h"

typedef struct {
    u8 unknown_00[0x13];
    u8 x;
    u8 y;
    u8 unknown_15[5];
    s16 first;
} TilePosition0806B274;

typedef struct {
    u8 unknown_00[0xC];
    u8 stride;
    u8 unknown_0D[7];
    u16 *tiles;
} TileMap0806B274;

typedef struct {
    u16 item;
    u8 quantity;
    u8 unknown_03;
} Item0806B274;

typedef struct {
    u8 unknown_0000[0x446D];
    u8 count;
    u8 unknown_446E[0x96];
    Item0806B274 items[0x178];
    u8 unknown_4AE4[0x117];
    u8 type;
    u8 unknown_4BFC[2];
    u8 field_4BFE;
    u8 unknown_4BFF[6];
    u8 counter;
} State0806B274;

extern State0806B274 *data_0200F428;
extern TileMap0806B274 data_030008B0;
extern u8 func_080CC9A0(u8 selector, u16 value);
extern void func_08070170(TilePosition0806B274 *position,
                          TileMap0806B274 *map, u8 row);
extern void func_0806E528(void);

/* Target [0x0806B274, 0x0806B338), 196 complete bytes:
 * 70b5061c18480368184a99180978051c002950d0164958180178013101700024
 * 1a22b35e2868134940180078834242da2a681149501800781919890052180f49
 * 5218118861f072fb0006002823d02868074a81180878272814d8301c0849221c
 * 04f04cff17e0000028f40002fe4b0000054c00006d440000fb4b000004450000
 * b0080003282802d103f014f903e04f2801d900200870601c0006040e032c0ad8
 * 1a25735f1a1905490868054d40190d1c00788242bcdb70bc01bc004728f40002
 * 6d440000
 */
void func_0806B274(TilePosition0806B274 *position)
{
    u8 row;

    if (data_0200F428->field_4BFE != 0) {
        data_0200F428->counter++;
        for (row = 0; row < 4 &&
             position->first + row < data_0200F428->count; row++) {
            if (func_080CC9A0(data_0200F428->type,
                             data_0200F428->items[position->first + row].item)) {
                if (data_0200F428->counter < 40)
                    func_08070170(position, &data_030008B0, row);
                else if (data_0200F428->counter == 40)
                    func_0806E528();
                else if (data_0200F428->counter >= 80)
                    data_0200F428->counter = 0;
            }
        }
    }
}
