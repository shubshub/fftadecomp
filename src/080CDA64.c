typedef unsigned char u8;

typedef struct {
    u8 unknown_00[0xEA];
    u8 flags;
} Object;

u8 func_080CDA64(const Object *object)
{
    u8 mask = 2;
    u8 flags = object->flags;

    if (!(flags & mask))
        return 0;
    return 1;
}
