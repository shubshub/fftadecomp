typedef unsigned char u8;

struct Context {
    u8 unknown_00[0x1A];
    u8 direction;
};

/* Target: 080C5434..080C5438, 4 bytes. */
u8 func_080C5434(const struct Context *context)
{
    return context->direction;
}
