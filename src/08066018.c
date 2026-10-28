typedef unsigned char u8;
typedef unsigned short u16;

struct Object {
    u8 unknown_00[4];
    u16 flags;
};

extern struct Object *func_08005BFC(void);

void func_08066018(void)
{
    struct Object *object = func_08005BFC();

    object->flags = 0x80;
}
