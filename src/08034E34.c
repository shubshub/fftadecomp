#include "ffta.h"

typedef struct {
    u8 mode : 3;
    u8 active : 1;
    u8 next : 3;
    u8 unknown : 1;
} __attribute__((packed)) AnimationFlags;

typedef struct {
    u8 unknown_00[0x9A];
    AnimationFlags first;
    u8 unknown_9B[0x32];
    s8 first_position;
    u8 unknown_CE[0x18];
    AnimationFlags second;
    u8 unknown_E7[0x32];
    s8 second_position;
} AnimationState;

extern AnimationState data_030009E0;

/* 08034E34..08034E88: 84 bytes, 38 reachable instructions. */
void func_08034E34(void)
{
    data_030009E0.first_position = 17;
    data_030009E0.second_position = 18;
    data_030009E0.first.active = 0;
    data_030009E0.first.next = 5;
    data_030009E0.first.mode = 0;
    data_030009E0.second.active = 0;
    data_030009E0.second.next = 5;
    data_030009E0.second.mode = 0;
}
