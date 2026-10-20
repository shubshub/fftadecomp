typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u8 func_08121D9C(void);
void func_08141728(u16 value);
void func_0812800C(void *context, u32 packed, u16 duration, u8 flags);

u32 func_08123714(void *context, const u8 *script)
{
    u8 flags = script[4];
    u32 duration = script[2] | (script[3] << 8);
    u32 value = script[1];
    u32 packed = 0;
    int index;

    for (index = 0; index < 4; index++, value <<= 8) {
        if ((flags >> index) & 1)
            packed |= value;
    }

    if ((flags & 1) && packed != 0)
        func_08141728(func_08121D9C());
    func_0812800C(context, packed, duration, flags);
    return 0x115;
}
