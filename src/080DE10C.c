typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct Object {
    u8 unknown_0[0x1F];
    s8 value;
} Object;

extern Object *func_080DD350(Object *object);
extern void func_080DE12C(Object *object, u16 command, int value);

/* 0x080DE10C: 30 bytes. Update an object using its stored signed value. */
void func_080DE10C(Object *object, u16 command)
{
    Object *state = func_080DD350(object);

    func_080DE12C(object, command, state->value);
}
