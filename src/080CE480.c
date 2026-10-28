typedef unsigned char u8;

struct Object {
    u8 unknown_00[0xE5];
    u8 value;
};

/* Target: 080CE480..080CE486, 6 bytes. */
void func_080CE480(struct Object *object, u8 value)
{
    object->value = value;
}
