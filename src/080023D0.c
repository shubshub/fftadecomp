/* 0x080023D0, 26 bytes. */
struct State080023D0 {
    unsigned char unknown_00[4];
    unsigned short field_04;
    unsigned char unknown_06;
    unsigned char flags_07;
    unsigned char unknown_08[3];
    unsigned char field_0B;
    unsigned char unknown_0C[2];
    unsigned char field_0E;
};

void func_080023D0(struct State080023D0 *state)
{
    if (state->flags_07 & 0x80)
        state->field_0E = state->field_0B;
    state->field_04 = 0;
}
