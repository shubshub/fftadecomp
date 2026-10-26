typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Object {
    u8 unknown_0[0x1F];
    s8 value;
    u8 unknown_20[0x10];
    u32 flags;
} Object;

extern Object *func_080DD350(Object *object);
extern void func_0809836C(Object *object, u16 command, int value, u16 duration);
extern void func_080DE12C(Object *object, u16 command, int value);

/* 0x080DE188: 104 bytes. Dispatch an object update using command control bits. */
void func_080DE188(Object *object, u16 command, u16 duration, u8 value)
{
    if (!(command & 0x4000))
        object->flags |= 2;
    else
        command &= 0xBFFF;

    if (command & 0x8000) {
        command &= 0x7FFF;
        func_0809836C(object, command, (s8)value, duration);
    } else {
        Object *state = func_080DD350(object);

        func_080DE12C(object, command, state->value);
    }
}
