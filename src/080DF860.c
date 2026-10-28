typedef unsigned char u8;
typedef signed char s8;

typedef struct {
    u8 unknown_0[0x1F];
    s8 value;
} Object;

extern void func_080DF870(Object *object, int value);

/* 0x080DF860: 14 bytes. Update the object using its stored signed value. */
void func_080DF860(Object *object)
{
    func_080DF870(object, object->value);
}
