typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_0[0x1F];
    s8 value;
} Object;

extern void func_0809836C(Object *object, u16 command, int value, u16 duration);

/* 0x080DE210: 36 bytes. Apply the supplied and stored signed object values. */
void func_080DE210(Object *object, s8 value)
{
    func_0809836C(object, 10, value, 0);
    func_0809836C(object, 9, object->value, 0);
}
