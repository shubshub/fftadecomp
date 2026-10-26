typedef unsigned char u8;
typedef unsigned int u32;

extern u32 func_08005BB0(void *object);
extern void func_08005B58(void *object);

static inline u8 object_finished(void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

/* 0x080D3F08..0x080D3F34: 44 bytes. */
void *func_080D3F08(void *object)
{
    if (object && object_finished(object)) {
        func_08005B58(object);
        return 0;
    }
    return object;
}
