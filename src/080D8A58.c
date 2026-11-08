#include "ffta.h"

typedef struct {
    u16 command;
    u16 unknown_02;
    void *first_destination;
    void *second_destination;
    u32 unknown_0C[2];
    u16 mode;
    u16 palette;
    u32 unknown_18;
} TilemapDescriptor;

typedef int (*TilemapCallback)(void *, void *, void *);

extern void *data_0200F430;
extern int func_080D8384(void *, void *, void *);
extern void *func_08005954(void *, TilemapCallback, u16, void *, void *);

/* Complete 080D8A58..080D8A98:
 * 30 B5 88 B0 0B 9D 00 06 00 0E 09 06 09 0E 01 AC
 * A0 82 20 1C C1 82 02 92 03 93 06 48 00 68 06 49
 * 06 4A 00 95 23 1C 2C F7 69 FF 08 B0 30 BC 02 BC
 * 08 47 00 00 30 F4 00 02 85 83 0D 08 14 08 00 00
 */
void *func_080D8A58(u8 mode, u8 palette, void *first_destination,
                   void *second_destination, void *parent)
{
    TilemapDescriptor descriptor;

    descriptor.mode = mode;
    descriptor.palette = palette;
    descriptor.first_destination = first_destination;
    descriptor.second_destination = second_destination;
    return func_08005954(data_0200F430, func_080D8384, 0x814,
                         &descriptor, parent);
}
