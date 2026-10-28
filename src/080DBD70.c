typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_0[8];
    u16 first;
    u16 second;
    u16 third;
} ObjectValues;

/* 0x080DBD70: 8 bytes. Set three adjacent halfword fields. */
void func_080DBD70(ObjectValues *object, u16 first, u16 second, u16 third)
{
    object->first = first;
    object->second = second;
    object->third = third;
}
