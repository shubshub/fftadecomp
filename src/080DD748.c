#include "ffta.h"

typedef struct PositionSourceLink PositionSourceLink;

extern PositionSourceLink *func_080DD760(PositionSourceLink *source,
                                       s16 *first, s16 *second, s16 *third,
                                       s16 value);

/* 0x080DD748 - 22 bytes.
 * Target: 10b581b002246442009400f005f801b010bc02bc0847
 */
PositionSourceLink *func_080DD748(PositionSourceLink *source,
                                s16 *first, s16 *second, s16 *third)
{
    return func_080DD760(source, first, second, third, -2);
}
