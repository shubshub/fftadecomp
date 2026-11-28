typedef unsigned char u8;

/* r0 passes straight through: func_080C286C reads the object (+4, +0x58,
 * +0x5A), and the only caller, func_080C045C, passes state->object
 * (0x080C0750). */
extern u8 func_080C286C(void *object);

/* Target: 080C47FC..080C480A, 14 bytes. */
u8 func_080C47FC(void *object)
{
    return func_080C286C(object);
}
