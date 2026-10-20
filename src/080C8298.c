typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} FlaggedObject;

u8 func_080C8298(const FlaggedObject *object)
{
    u8 result = 0;

    if (object != 0) {
        u16 flags = object->flags & 0x1000;
        result = flags != 0;
    }

    return result;
}
