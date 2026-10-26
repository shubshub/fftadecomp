typedef unsigned char u8;

struct State {
    u8 unknown[0xE4];
    u8 value;
};

void func_080CE478(struct State *state, u8 value)
{
    state->value = value;
}
