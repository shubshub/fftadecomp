typedef unsigned short u16;
typedef signed short s16;

extern u16 func_080DD6E0(void *object);

/* 0x080DC224: 68 bytes. Compute offsets for the supplied dimensions. */
void func_080DC224(void *object, s16 width, s16 height, s16 *x, s16 *y)
{
    if (x)
        *x = 16 - width;
    if (y) {
        *y = 48 - height;
        if (func_080DD6E0(object) == 0x51)
            *y -= 4;
    }
}
