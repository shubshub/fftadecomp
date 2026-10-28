typedef unsigned char u8;

struct State {
    u8 unknown[0xDC];
    u8 value;
};

void func_080CE438(struct State *state, u8 value)
{
    state->value = value;
}
