typedef unsigned char u8;

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

void func_080CDE5C(Object *object, u8 enabled)
{
    u8 mask = 4;

    object->flags &= ~mask;
    if (enabled)
        object->flags |= mask;
}
