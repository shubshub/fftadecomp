typedef unsigned char u8;
typedef signed char s8;

extern u8 func_0801CC7C(u8 x, u8 y);
extern u8 func_0801CC18(u8 x, u8 y);

int func_0809D79C(s8 x, s8 y)
{
    if (x < 0 || y < 0 || x > 15 || y > 15 || !func_0801CC7C(x, y))
        return -1;
    return func_0801CC18(x, y);
}
