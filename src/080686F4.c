#include "ffta.h"

// Complete [0x080686F4, 0x080687D8): 228 bytes.
// Target: f0b557464e464546e0b483b04268111c50310091011c283100239846897c029181320192051cc03589469a460ae0029f78008144802040048244012188444246032a44dc534619160098aff72dfa0004e0277f03c019030c002648460404220c0199087840450dd150002818b0273f02d91901800299501840002818004a0ce001b0000050002818c0273f02d91901800299501840002818114a9918018080277f02e4190136981c0004030c052ed6dd504601160098aff7ddf9041c2404240c0098aff717fa000400148442afd103b038bc9846a146aa46f0bc01bc0047000001c00000

typedef struct {
    u8 unknown_00[0x50];
    u8 list[0x31];
    u8 selected;
} MenuOwner080686F4;

typedef struct {
    u8 unknown_00[0x12];
    u8 stride;
} MenuControl080686F4;

typedef struct {
    u8 unknown_00[4];
    MenuOwner080686F4 *owner;
    u8 unknown_08[0x20];
    MenuControl080686F4 control;
    u8 unknown_3c[0x84];
    u16 entries[1];
} MenuContext080686F4;

extern u16 func_08017B9C(void *list, s8 row);
extern u16 func_08017B68(void *list, s8 row);
extern s16 func_08017BE8(void *list);

void func_080686F4(MenuContext080686F4 *context)
{
    void *list = context->owner->list;
    MenuControl080686F4 *control = &context->control;
    s32 row = 0;
    u8 stride = control->stride;
    u8 *selected = &context->owner->selected;
    s32 column;
    u16 tile;
    u16 position;

    do {
        tile = func_08017B9C(list, row);
        tile += 0x1C;
        for (column = 0; column < 6; column++, tile += 2) {
            position = (row * 2 + 1) * stride + column;
            if (*selected == row) {
                context->entries[position] = tile + 0xB000;
                context->entries[position + stride] = tile + 0xB001;
            } else {
                context->entries[position] = tile + 0xC000;
                context->entries[position + stride] = tile + 0xC001;
            }
        }
        if (func_08017B68(list, row) == func_08017BE8(list))
            break;
    } while (++row < 4);
}
