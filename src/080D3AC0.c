typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[2];
    u16 flags;
} State;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* 0x080D3AC0..0x080D3AF6: 54 bytes. */
void func_080D3AC0(u8 enabled)
{
    State *state = func_08005BFC(data_020159C0);

    if (enabled)
        state->flags &= 0xFFEF;
    else
        state->flags |= 0x10;
}
