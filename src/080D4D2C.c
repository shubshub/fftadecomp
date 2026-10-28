typedef unsigned char u8;
typedef unsigned int u32;

extern u32 func_0800C148(void *object);
extern void func_0800C224(void *object);
extern void func_0800C1C8(u8 mode);

/* 0x080D4D2C..0x080D4D58: 44 bytes. */
void *func_080D4D2C(void *object, u8 mode)
{
    if (object && func_0800C148(object)) {
        func_0800C224(object);
        func_0800C1C8(mode);
        return 0;
    }
    return object;
}
