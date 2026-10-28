/* 080359E4..08035A20: 60 bytes, 24 reachable Thumb instructions. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;

typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[0xC8];
} MenuSlot;

typedef struct {
    u8 unknown_000[0x4B8];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4C4[0x984 - 0x4C4];
    MenuSlot slots[1];
} MenuContext;

extern MenuContext *g_state_03002810;

void func_080359E4(s32 index, u8 value)
{
    g_state_03002810->slots[index].state = 0;
    g_state_03002810->closed[index] = value;
    g_state_03002810->active[index] = 0;
}
