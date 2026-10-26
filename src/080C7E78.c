typedef unsigned char u8;
typedef unsigned int u32;

struct Object {
    u8 unknown_00[0x14];
    u32 flags;
};

/* Target: 080C7E78..080C7E94, 28 bytes. */
int func_080C7E78(struct Object *object, struct Object **result)
{
    if (object->flags & 1)
        return 1;
    *result = object;
    return 0;
}
