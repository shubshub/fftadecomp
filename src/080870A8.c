#include "ffta.h"

typedef struct {
    u8 unknown_000[0xbf5];
    u8 mode;
} MenuState080870A8;

typedef struct {
    u8 unknown_000[0x148];
    u16 *destination;
} TileRenderer080870A8;

extern MenuState080870A8 *data_03002818;
extern TileRenderer080870A8 data_030009E0;
extern const u16 data_0894FF54[];
extern void func_08035578(const u16 *source, u16 *destination,
                         u32 count, u16 offset);

/* Complete target [0x080870A8, 0x080870E0): 56 bytes, 18 instructions. */
void func_080870A8(void)
{
    data_03002818->mode = 4;
    func_08035578(data_0894FF54, data_030009E0.destination, 26, 50);
}
