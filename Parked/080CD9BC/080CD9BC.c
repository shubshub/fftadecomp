typedef unsigned char u8;

typedef struct {
    u8 unknown_00[0xE9];
    u8 flags;
} Object;

u8 func_080CD9BC(const Object *object)
{
    u8 flags = object->flags;

    if (!(flags & 0x10))
        return 0;
    return 1;
}
