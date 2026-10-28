#include "ffta.h"

/* 0x080DBDA0..0x080DBDC8: 40 bytes / 19 instructions. */
struct Position080DBDA0 {
    u8 unknown_00[8];
    s16 first;
    s16 second;
    s16 third;
};

extern void func_0801C918(s16 first, s16 second, s16 third,
                         s16 *first_output, s16 *second_output, s16 *third_output);

void func_080DBDA0(const struct Position080DBDA0 *position,
                   s16 *first_output, s16 *second_output, s16 *third_output)
{
    func_0801C918(position->first, position->second, position->third,
                  first_output, second_output, third_output);
}
