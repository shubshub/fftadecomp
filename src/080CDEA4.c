typedef unsigned char u8;

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

void func_080CDEA4(Object *object, u8 enabled)
{
    u8 mask = 0x10;

    object->flags &= ~mask;
    if (enabled)
        object->flags |= mask;
}
