typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

struct Unit {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
};

struct Owner {
    struct Unit *unit;
};

struct Context {
    struct Owner *owner;
    u8 unknown_04[8];
    struct Owner **owners;
    u8 unknown_10[2];
    u16 count;
};

extern int abs(int value);
extern u16 func_08002804(void);
extern u8 func_0809D6BC(s8 dx, s8 dy);

/* Target: 080C4964..080C4A40, 220 bytes. */
u8 func_080C4964(struct Context *context, u8 x, u8 y)
{
    s16 nearest = 0x100;
    u8 direction = (s16)func_08002804() % 4;
    int i;

    for (i = 0; i < context->count; i++) {
        struct Owner *other = context->owners[i];
        s16 distance;

        if (other == context->owner)
            continue;

        distance = abs(other->unit->x - x) + abs(other->unit->y - y);
        if (distance > nearest)
            continue;
        if (distance == nearest && (func_08002804() % 2))
            continue;

        nearest = distance;
        direction = func_0809D6BC(other->unit->x - x, other->unit->y - y);
    }

    return direction;
}
