typedef unsigned char u8;
typedef signed char s8;
typedef signed short s16;

typedef struct {
    u8 unknown_0[0xA];
    s8 x;
    s8 y;
} Position;

extern Position *func_080A880C(void *object);

/* 0x080D8B5C: 30 bytes. Read the object's signed byte coordinates. */
void func_080D8B5C(void *object, s16 *x, s16 *y)
{
    Position *position = func_080A880C(object);

    *x = position->x;
    *y = position->y;
}
