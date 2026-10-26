typedef signed char s8;
typedef unsigned short u16;

extern void *func_080DD350(void *object);
extern void func_0809A2D8(void *object, u16 command, int value);

/* 0x080DE12C: 36 bytes. Forward a command and signed value to the object. */
void func_080DE12C(void *object, u16 command, s8 value)
{
    void *state = func_080DD350(object);

    func_0809A2D8(state, command, value);
}
