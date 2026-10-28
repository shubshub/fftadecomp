typedef unsigned char u8;

struct Object {
    u8 unknown_00[0xDB];
    u8 value;
};

/* Target: 080CE430..080CE436, 6 bytes. */
void func_080CE430(struct Object *object, u8 value)
{
    object->value = value;
}
