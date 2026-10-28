typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

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
    u16 x;
    u16 y;
    u8 unknown_08[2];
    s8 dx;
    s8 dy;
};

static inline void set_direction(s8 *dx, s8 *dy, s8 direction)
{
    switch (direction) {
    case 0:
        *dx = 0;
        *dy = 1;
        break;
    case 1:
        *dx = -1;
        *dy = 0;
        break;
    case 2:
        *dx = 0;
        *dy = -1;
        break;
    case 3:
        *dx = 1;
        *dy = 0;
        break;
    default:
        *dx = 0;
        *dy = 0;
        break;
    }
}

void func_0809CC3C(struct Context *context, struct Owner *owner, s8 direction)
{
    set_direction(&context->dx, &context->dy, direction);

    context->owner = owner;
    context->x = (context->dx + owner->unit->x) * 32 + 16;
    context->y = (context->dy + owner->unit->y) * 32 + 16;
    context->dx *= 4;
    context->dy *= 4;
}
