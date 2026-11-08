#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2FC2];
    u8 mode : 2;
    u8 unknown_02 : 6;
} Selection08135D6C;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} Layer08135D6C;

typedef void (*BufferCopier08135D6C)(void *destination, const void *source,
                                    u32 size);

extern Selection08135D6C g_state_02000000;
typedef struct {
    u8 unknown_0000[0x8000];
    u16 first[0x100];
    u16 second[0x100];
} Palette08135D6C;

extern Palette08135D6C *data_0200F3B0;
extern Layer08135D6C data_03000E60;
extern Layer08135D6C data_03000E80;
extern Layer08135D6C data_030008B0;
extern const u8 *const data_083A8C54[];
extern BufferCopier08135D6C data_0836D4BC[];
extern const u8 data_08958DD8[];
extern const u8 data_08960EC0[];
extern const u8 data_08964838[];
extern const u16 data_08957378[];
extern const u16 data_08957878[];
extern const u16 data_08957D28[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08135FA0(const u16 *source, u16 *destination, u16 count,
                          u8 width, u16 offset);
extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier08135D6C callback);

/* Complete target [0x08135D6C, 0x08135E88), 284 bytes:
 * 70b556464d46444670b481b03048c021c9048022d2010bf073fd2e482e492f4a0bf06efd
 * 2e482f492f4a0bf069fd2f482f494969a022920000240094202300f0f9f82c482c494969
 * 9625ad0000942a1c1e2300f0eff829482949496900942a1c1e2300f0e7f8274881462748
 * 2868802109028a465044254a9046254c2549641821788907c90e414409688026b6004a46
 * 1368321c0cf026fa286882210902401821788907490f01318900414409684a461368321c
 * 0cf016fa286850441649018001b038bc9846a146aa4670bc01bc0047d88d9508c00e9608
 * 00800006d41c00003848960800000106bc16000078739508600e000378789508800e0003
 * 287d9508b0080003bcd43608b0f30002548c3a0800000002c22f0000ff7f0000
 */
void func_08135D6C(void)
{
    BufferCopier08135D6C *copy;

    func_0814186C(data_08958DD8, (void *)0x06000000, 0x4000);
    func_0814186C(data_08960EC0, (void *)0x06008000, 0x1CD4);
    func_0814186C(data_08964838, (void *)0x06010000, 0x16BC);
    func_08135FA0(data_08957378, data_03000E60.tiles, 0x280, 32, 0);
    func_08135FA0(data_08957878, data_03000E80.tiles, 600, 30, 0);
    func_08135FA0(data_08957D28, data_030008B0.tiles, 600, 30, 0);
    copy = data_0836D4BC;
    func_08142250(data_0200F3B0->first,
                  data_083A8C54[g_state_02000000.mode * 2], 0x200,
                  copy[0]);
    func_08142250(data_0200F3B0->second,
                  data_083A8C54[g_state_02000000.mode * 2 + 1], 0x200,
                  copy[0]);
    data_0200F3B0->first[0] = 0x7FFF;
}
