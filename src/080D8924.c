#include "ffta.h"

/* Complete target: [0x080D8924, 0x080D89D0), 172 bytes. */
typedef struct {
    u8 unknown_00[0x0A];
    s8 x;
    s8 y;
} TilePosition080D8924;

typedef struct {
    u16 state;
    u16 unknown_02;
    const s16 *position;
    u8 unknown_08[0x0C];
    u16 delay;
    u16 flags;
    u8 unknown_18[4];
} EffectEvent080D8924;

typedef int (*SchedulerCallback080D8924)(void *task, void *descriptor,
                                         void *payload);

extern u8 func_080D8858(void *object, u16 flags);
extern u8 func_080DD698(void *object, u16 mask);
extern u8 func_080DD494(void *object);
extern void *func_080A880C(void *record);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801CA78(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output,
                         s16 *third_output);
extern int func_080D82E0(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(SchedulerCallback080D8924 callback, u16 payload_size,
                           void *descriptor, void *parent);

/* The coordinate read shared with src/080D8BD8.c and src/080D8CD4.c, text
 * unchanged: the same ldrsb/strh pairs are at 0x080D8962 here and at
 * 0x080D8BFC and 0x080D8CE2 in those functions. */
static inline void get_coordinates(void *object, s16 *x, s16 *y)
{
    TilePosition080D8924 *position = func_080A880C(object);

    *x = position->x;
    *y = position->y;
}

u8 func_080D8924(void *object, u16 flags, u16 delay, void *parent)
{
    EffectEvent080D8924 event;
    s16 x, y;

    if (delay == 0)
        return func_080D8858(object, flags);

    if (!func_080DD698(object, 0x20))
        return func_080DD494(object);

    get_coordinates(object, &x, &y);
    {
        s16 position[3];
        u8 height = func_0801CC18(x, y);

        func_0801CA78(x, height, y, &position[0], &position[1], &position[2]);
        event.position = position;
        event.delay = delay;
        event.flags = flags;
        func_08005B6C(func_080D82E0, 0x0C, &event, parent);
    }
    return 0;
}
