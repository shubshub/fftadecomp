/* Target 08021E3C, complete 34 bytes:
 * 10b5021c131c0c20115e0e24105f814201da081c02e00c24185f013810bc02bc0847
 */
struct State08021E3C {
    unsigned char unknown_00[12];
    short current;
    short limit;
};

int func_08021E3C(void *data)
{
    struct State08021E3C *state = data;
    if (state->current >= state->limit)
        return state->current - 1;
    return state->current;
}
