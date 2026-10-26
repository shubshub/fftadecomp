typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[2];
    u16 flags;
} State;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* 0x080D39F0..0x080D3A12: 34 bytes. */
u8 func_080D39F0(void)
{
    State *state = func_08005BFC(data_020159C0);

    if (state->flags & 0x20)
        return 1;
    return 0;
}
