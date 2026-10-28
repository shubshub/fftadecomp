typedef unsigned char u8;
typedef unsigned short u16;

extern u16 func_080B43EC(u16 first, u16 second);
extern u16 func_080B42E4(u16 first, u16 second);

/* Target: 080B7C2C..080B7C4E, 34 bytes. */
u16 func_080B7C2C(u16 first, u16 second, u8 enabled)
{
    u16 result;

    if (enabled)
        result = func_080B43EC(first, second);
    else
        result = func_080B42E4(first, second);

    return result;
}
