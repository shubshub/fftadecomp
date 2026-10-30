#include "ffta.h"

extern u32 func_080C8570(u8 first, u8 second, u8 selector);
extern const u8 *const g_table_0851BA84[];

/* The bounds-and-row operation is the defining func_080CD428 body,
 * with its actual u32 accessor result explicitly narrowed to u8. */
static inline const u8 *table_bounds(u8 id, u8 table_index,
                                   u8 *first_output, u8 *second_output)
{
    u8 first = (u8)func_080C8570(id, id, 0x25);
    u8 second = (u8)func_080C8570(id, id, 0x26);

    if (first_output)
        *first_output = first;
    if (second_output)
        *second_output = second;

    return g_table_0851BA84[table_index];
}

/* Target [0x080CD2C4, 0x080CD362), 158 bytes:
 * f0b54f464646c0b481b0071c0d062d0ebe79e846012068448146281c291c2522fbf744f9041c2406240e281c291c2622fbf73cf90006000e41460c70494608700f4ab600b618366869460b7883421ed89046051cdc0030198079002812d0381c4030c01802787f21b87980004044006800191140c079814204d2002008e0000084ba5108581c0006030eab42e2d9012001b018bc9846a146f0bc02bc0847
 */
u32 func_080CD2C4(const u8 *object, u8 id)
{
    u8 first;
    u8 last;
    u8 index;
    const u8 *table = table_bounds(id, object[6], &first, &last);

    for (index = first; index <= last; index++) {
        if (table[index * 8 + 6] != 0 &&
            (object[0x40 + index] & 0x7F) <
                g_table_0851BA84[object[6]][index * 8 + 7])
            return 0;
    }
    return 1;
}
