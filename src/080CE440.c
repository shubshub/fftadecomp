typedef unsigned char u8;

struct Object {
    u8 unknown_00[0xDD];
    u8 value;
};

/* Target: 080CE440..080CE446, 6 bytes. */
void func_080CE440(struct Object *object, u8 value)
{
    object->value = value;
}
