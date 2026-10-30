typedef unsigned char u8;
typedef unsigned short u16;

struct State {
    u8 unknown_0000[0x1112];
    u16 flags;
};

/* 0x080B7F18..0x080B7F4C: 52 target bytes, including literal pools. */
void func_080B7F18(struct State *state, u8 enabled)
{
    if (enabled)
        state->flags |= 0x100;
    else
        state->flags &= ~0x100;
}
