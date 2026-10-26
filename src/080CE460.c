typedef unsigned char u8;

struct State {
    u8 unknown[0xE1];
    u8 value;
};

void func_080CE460(struct State *state, u8 value)
{
    state->value = value;
}
