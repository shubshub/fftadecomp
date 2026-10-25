/* 0x080EAB34 - 172 bytes
 * 30b582b0041c151c0988012946d0012902dc002905d041e080204000814215d03ce0084800910191012103220023ecf75dfb0548211ce9f797f928610220e8812ce00000484d8f08e8d694082869e9f7c1f92861288801302880287b1cf75cff011c0904a87b2a7b8018287368680e4a80186860ac68a63cac6000022402240c00140915401a00040014032118f7a2fc24042414201c032118f7c4fc002002b030bc02bc08470000b4feffff
 */
#include "ffta.h"

typedef struct ScrollDescriptor {
    u16 phase;
} ScrollDescriptor;

typedef struct ScrollState {
    u16 counter;
    u16 unknown_02;
    s32 x;
    s32 y;
    u8 angle;
    u8 unknown_0D;
    u16 angle_step;
    void *child;
} ScrollState;

void func_080D7220(const void *record, u8 bank, u8 layer,
                   s16 x, s16 y, u16 flags);
void *func_080D3E9C(const void *record, void *parent);
void *func_080D3F08(void *child);
s32 func_08007A4C(u8 angle);
void func_08003508(s16 coordinate, u8 layer);
void func_08003558(s16 coordinate, u8 layer);

u32 func_080EAB34(void *task, void *descriptor, void *payload)
{
    ScrollDescriptor *control = descriptor;
    ScrollState *state = payload;
    s16 wave_offset;
    s16 x;
    s16 y;

    switch (control->phase) {
    case 0:
        func_080D7220((const void *)0x088F4D48, 1, 3, 0, 0, 0);
        state->child = func_080D3E9C((const void *)0x0894D6E8, task);
        state->angle_step = 2;
        break;
    case 1:
        break;
    case 0x100:
        state->child = func_080D3F08(state->child);
        state->counter++;
        wave_offset = (s16)func_08007A4C(state->angle) >> 4;
        state->angle += state->angle_step;
        state->x -= 332;
        state->y -= 166;
        x = state->x >> 8;
        y = state->y >> 8;
        func_08003508(x - wave_offset, 3);
        func_08003558(y, 3);
        break;
    }
    return 0;
}
