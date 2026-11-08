#include "ffta.h"

/* Complete target [0x0812C700, 0x0812C7B8): 184 bytes. */
typedef struct {
    s8 x;
    s8 y;
    s8 unknown_02[2];
} Direction;

extern const Direction data_083A842C[];
extern const s8 data_083A843C[];
extern const s8 data_083A8440[];
extern u8 func_0812C684(s8 x, s8 y, s8 origin_x, s8 origin_y,
                       s8 direction_x, s8 direction_y);

s32 func_0812C700(s8 source_x, s8 source_y, s8 target_x, s8 target_y,
                  s8 direction)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        s32 facing = direction + data_083A843C[i];
        if (facing > 3)
            facing -= 4;
        if (facing < 0)
            facing += 4;
        if (func_0812C684(source_x, source_y,
                         target_x + data_083A842C[facing].x * data_083A8440[i],
                         target_y + data_083A842C[facing].y * data_083A8440[i],
                         data_083A842C[facing].x, data_083A842C[facing].y) == 1)
            return i;
    }
    return 0;
}
