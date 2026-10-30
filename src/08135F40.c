#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2FC2];
    u8 mode : 2;
    u8 unknown_02 : 6;
} Selection08135F40;

extern Selection08135F40 g_state_02000000;
extern const u8 *const data_083A8C54[];
extern u8 data_03003860[];
extern s32 func_08000F48(const void *source, void *destination, u16 count);

/* Target [0x08135F40, 0x08135FA0), 96 complete bytes:
 * 70b5464640b412488046124c1249641820788007c00e40440068
 * 104d80267600291c321ccaf6f0ff20788007400f013080004044
 * 0068802189006d18291c321ccaf6e2ff08bc984670bc01bc0047
 * 0000548c3a0800000002c22f000060380003
 */
void func_08135F40(void)
{
    const u8 *const *sources = data_083A8C54;
    u32 index = g_state_02000000.mode * 2;

    func_08000F48(sources[index], data_03003860, 0x100);
    index = g_state_02000000.mode * 2 + 1;
    func_08000F48(sources[index], data_03003860 + 0x200, 0x100);
}
