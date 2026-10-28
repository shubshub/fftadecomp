#include "ffta.h"

/* 0x080DD760..0x080DD7AE: 78 bytes. */
typedef struct PositionSourceLink {
    struct PositionSourceLink *source;
} PositionSourceLink;

extern void func_080DBDC8(PositionSourceLink *source, s16 *first, s16 *second);
extern void func_080DE268(PositionSourceLink *source);
extern void func_080DE10C(PositionSourceLink *source, u16 value);

PositionSourceLink *func_080DD760(PositionSourceLink *source,
                                  s16 *first, s16 *second, s16 *third,
                                  s16 value)
{
    source = source ? source->source : 0;
    if (third == 0)
        func_080DBDC8(source, first, second);
    else
        func_080DBD5C((Struct080DBD5C *)source, first, second, third);
    if (value != -1) {
        if (value == -2)
            func_080DE268(source);
        else
            func_080DE10C(source, value);
    }
    return source;
}
