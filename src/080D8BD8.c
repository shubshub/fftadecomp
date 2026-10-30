#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0A];
    s8 x;
    s8 y;
} TilePosition080D8BD8;

extern void *func_080A880C(void *record);
extern u8 func_0801CC18(u8 column, u8 row);
extern void func_0801CA78(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output,
                         s16 *third_output);
extern void func_0801C918(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output,
                         s16 *third_output);

static inline void get_coordinates(void *object, s16 *x, s16 *y)
{
    TilePosition080D8BD8 *position = func_080A880C(object);

    *x = position->x;
    *y = position->y;
}

static inline void get_world_coordinates(void *object, s16 *first_output,
                                          s16 *second_output,
                                          s16 *third_output)
{
    s16 x, y;
    u8 height;

    get_coordinates(object, &x, &y);
    height = func_0801CC18(x, y);
    func_0801CA78(x, height, y,
                   first_output, second_output, third_output);
}

/* Complete target: [0x080D8BD8, 0x080D8C58), 128 bytes. */
void func_080D8BD8(void *object, s16 *first_output, s16 *second_output,
                   s16 *third_output)
{
    s16 first, second, third;

    get_world_coordinates(object, &first, &second, &third);
    func_0801C918(first, second, third,
                  first_output, second_output, third_output);
}
