typedef unsigned char u8;

struct Context;

extern struct Context *data_020101F0;
extern u8 func_080BCED0(struct Context *context, u8 value);

/* Target: 080BD130..080BD14C, 28 bytes. */
u8 func_080BD130(u8 value)
{
    return func_080BCED0(data_020101F0, value);
}
