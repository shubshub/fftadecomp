typedef unsigned char u8;

struct Object {
    u8 unknown_00[0xDE];
    u8 value;
};

/* Target: 080CE448..080CE44E, 6 bytes. */
void func_080CE448(struct Object *object, u8 value)
{
    object->value = value;
}
