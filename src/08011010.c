/* 0x08011010, 4 bytes: 80897047. */
struct State08011010 {
    unsigned char unknown_00[0x0C];
    unsigned short field_0C;
};

unsigned short func_08011010(const struct State08011010 *state)
{
    return state->field_0C;
}
