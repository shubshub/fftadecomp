#include "ffta.h"

/* Complete target [0x080D6798, 0x080D694E), 438 bytes:
 * f0b557464e464546e0b492b0029001931a981b9b1c9c1d9d1e9eb1461f9e209fb8460904090c03911204120c04920006
 * 000e05901b061b0e06932404240c07942d062d0e08954846000681463606360e41460906090e09910021684601800022
 * 0a9201270b9701200c90494600290bd08022d2000a92334f0b970599c819039a10180004000c0390002e0ed080263601
 * 301c0a9f07430a972a480c9006990818049a10180004000c049000230021069eb34278d2049f380400140a0411144018
 * 000400140f9201330e930c990904109100285bdb1f2859dc8001029a10180d9000250021059eb54250d2039f38040014
 * 824615488146090408145044000400148846002834db1f2832dc40000d990818119001a86946099afff7c4fe0004020c
 * 079e002e02d1089f002f1dd0079908040614089c131c4f463b404b4506d1101c10e00000ffff0000ff030000100bc027
 * 3f01391c0a4099190904001900070843000c10430004020c0a98424011990a80681c0006050e424611140b9e30040014
 * 09180904090c059fbd42b4d30e990806030e0f9a1014109e311440180004010c069fbb4286d312b038bc9846a146aa46
 * f0bc01bc0047
 */

extern u16 func_080D663C(const u16 **cursor, u16 *index, u8 encoded);

void func_080D6798(u16 *destination, u16 x, u16 y, const u16 *source,
                   u8 width, u8 height, u16 value_offset,
                   u8 upper_nibble_offset, u8 reverse_x, u8 reverse_y,
                   u8 encoded)
{
    u16 index = 0;
    u16 flip_mask = 0;
    u16 x_step = 1;
    u16 y_step = 1;
    u16 x_displacement;
    u16 y_displacement;
    u8 row;
    u8 column;

    if (reverse_x) {
        flip_mask = 0x400;
        x_step = -1;
        x += width - 1;
    }
    if (reverse_y) {
        flip_mask |= 0x800;
        y_step = -1;
        y += height - 1;
    }

    for (row = 0, y_displacement = 0; row < height;
         row++, y_displacement += (s16)y_step) {
        s16 row_position = (s16)y + (s16)y_displacement;
        u16 *line;

        if (row_position < 0 || row_position > 31)
            continue;
        line = destination + row_position * 32;
        for (column = 0, x_displacement = 0; column < width;
             column++, x_displacement += (s16)x_step) {
            s16 column_position = (s16)x + (s16)x_displacement;
            u16 value;

            if (column_position < 0 || column_position > 31)
                continue;
            value = func_080D663C(&source, &index, encoded);
            if (value_offset != 0 || upper_nibble_offset != 0) {
                u16 lower = value & 0x3FF;

                if (lower != 0x3FF) {
                    value = (u16)(lower + (s16)value_offset)
                          | (value & 0xC00)
                          | (((value >> 12) + upper_nibble_offset) << 12);
                }
            }
            line[column_position] = value ^ flip_mask;
        }
    }
}
