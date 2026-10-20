typedef unsigned char u8;
typedef unsigned int u32;

void *func_081255C8(u32 selector);
void func_08121DD0(void *object);

u32 func_08123968(void *context, const u8 *script)
{
    func_08121DD0(func_081255C8(script[1]));
    return 0x110;
}
