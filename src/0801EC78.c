#include "ffta.h"

struct PackedEntry0801EC78 {
    u16 first;
    u16 second;
    u16 third;
} __attribute__((packed));

struct PackedList0801EC78 {
    u16 count;
    struct PackedEntry0801EC78 entries[1];
} __attribute__((packed));

extern u8 func_0801E954(s16 first, s16 second, s16 third, s16 fourth,
                        s16 fifth, const struct PackedEntry0801EC78 *entry,
                        u8 first_option, u8 second_option);

/* Complete [0x0801EC78, 0x0801ED24): 172 bytes, 85 instructions. */
void func_0801EC78(u16 first, u16 second, u16 third, u16 fourth, u16 fifth,
                   const struct PackedList0801EC78 *list, u8 *results,
                   u8 first_option, u8 second_option)
{
    u16 i;

    for (i = 0; i < list->count; i++)
        results[i] = func_0801E954(first, second, third, fourth, fifth,
                                  &list->entries[i], first_option, second_option);
}
