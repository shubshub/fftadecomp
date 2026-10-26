typedef unsigned char u8;

struct Object {
    u8 unknown_00[0xE2];
    u8 value;
};

/* Target: 080CE468..080CE46E, 6 bytes. */
void func_080CE468(struct Object *object, u8 value)
{
    object->value = value;
}
