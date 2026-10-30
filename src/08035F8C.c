typedef unsigned char u8;
typedef unsigned int u32;

struct Window {
    u8 unknown_00[0x64];
    u8 field_64;
    u8 field_65;
};

struct Context {
    u32 unknown_00;
    struct Window *window;
};

struct State {
    u8 unknown_0000[0x2FBA];
    u8 field_2FBA;
    u8 field_2FBB;
};

extern struct Context *g_state_03002810;
extern struct State g_state_02000000;

/* 0x08035F8C..0x08035FC4: 56 target bytes, including literal pools. */
void func_08035F8C(void)
{
    struct Window *window = g_state_03002810->window;
    struct State *state = &g_state_02000000;

    window->field_64 = state->field_2FBB;
    g_state_03002810->window->field_65 = state->field_2FBA;
}
