#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 job;
    u8 unknown_07[0x39];
    u8 ability_points[0];
} Unit;

typedef struct {
    u8 unknown_00[6];
    u8 type;
    u8 required_points;
} AbilityInfo;

extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern AbilityInfo *const g_table_0851BA84[];

/* An inlined copy of func_080CD428 (src/080CD428.c). */
static inline AbilityInfo *ability_range(u8 id, u8 index, u8 *first_output, u8 *second_output)
{
    u8 first = func_080C8570(id, id, 0x25);
    u8 second = func_080C8570(id, id, 0x26);

    if (first_output)
        *first_output = first;
    if (second_output)
        *second_output = second;

    return g_table_0851BA84[index];
}

/* An inlined copy of func_080CD480 (src/080CD480.c), on 8-byte entries. */
static inline AbilityInfo *ability_info(u8 first, u8 second)
{
    return g_table_0851BA84[first] + second;
}

/* Target [0x080CD2C4, 0x080CD362), 158 bytes:
 * f0b54f464646c0b481b0071c0d062d0ebe79e846012068448146281c291c2522fbf744f9041c2406240e281c291c2622fbf73cf90006000e41460c70494608700f4ab600b618366869460b7883421ed89046051cdc0030198079002812d0381c4030c01802787f21b87980004044006800191140c079814204d2002008e0000084ba5108581c0006030eab42e2d9012001b018bc9846a146f0bc02bc0847
 */
u8 func_080CD2C4(void *unit, u8 id)
{
    u8 first;
    u8 last;
    u8 i;
    AbilityInfo *abilities = ability_range(id, ((Unit *)unit)->job, &first, &last);

    for (i = first; i <= last; i++) {
        /* The type comes from the row saved before the loop at 080CD30A. */
        AbilityInfo *info = &abilities[i];

        if (info->type != 0 &&
            (((Unit *)unit)->ability_points[i] & 0x7F) < ability_info(((Unit *)unit)->job, i)->required_points)
            return 0;
    }
    return 1;
}
