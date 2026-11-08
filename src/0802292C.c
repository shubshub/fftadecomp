#include "ffta.h"

typedef struct {
    u8 unknown_00[0x94];
    u16 flags;
} State0802292C;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern u8 data_02003CB0[];
extern u8 data_03003A60[];
extern BufferCopier data_0836D4BC[];
extern State0802292C g_state_0200F390;
extern void func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *source, void *destination, u32 control);
extern const u8 *func_080CBA3C(u8 index);
extern u8 *func_080CBA84(u32 index);
extern void func_0802B5A8(u32 mode);
extern void func_0802B8E8(void);

/* Complete [0x0802292C, 0x08022A04): 216 bytes.
 * f0b54f464646c0b40006070eb846294c01203840002813d02749201ce2f778fd26498822
 * d200201c1ef188ff2449201ce2f76efd2349a8225200201c1ef17eff02208146381c4946
 * 0840002817d01e4e1e4c0020a9f05cf8011c8025ad003368201c2a1c1ff15efc19482418
 * 0020a9f073f8011c3368201c2a1c1ff153fc04203840002802d0002008f0f8fd08204146
 * 0140002906d10f489430018848460840002801d008f08aff18bc9846a146f0bc01bc0047
 * b03c00027cbc3b0800250106ccc63b0880920006bcd43608603a000300feffff90f30002
 */
void func_0802292C(u8 mask)
{
    u8 *buffer = data_02003CB0;

    if (mask & 1) {
        func_0800543C(buffer, (const void *)0x083BBC7C);
        func_08141868(buffer, (void *)0x06012500, 0x440);
        func_0800543C(buffer, (const void *)0x083BC6CC);
        func_08141868(buffer, (void *)0x06009280, 0x150);
    }
    if (mask & 2) {
        data_0836D4BC[0](data_03003A60, func_080CBA3C(0), 0x200);
        data_0836D4BC[0](data_03003A60 - 0x200, func_080CBA84(0), 0x200);
    }
    if (mask & 4)
        func_0802B5A8(0);
    if ((mask & 8) || (g_state_0200F390.flags & 2))
        func_0802B8E8();
}
