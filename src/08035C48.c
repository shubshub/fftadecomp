#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x1F64];
    u32 field_1F64;
} State08035C48;

extern State08035C48 g_state_02000000;
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08035BD4(u16 *destination, u16 digits, u32 value, u16 flags);
extern void func_0808A604(u8 index, u8 command);

/* Target [0x08035C48, 0x08035C80), 56 complete bytes:
 * 10b50b480b4940180468022001210122012355f043fed0231b02
 * 0821221cfff7b5ff0220022154f0c9fc10bc01bc004700000002641f0000
 */
void func_08035C48(void)
{
    u32 value = g_state_02000000.field_1F64;
    u16 *destination = func_0808B8E4(2, 1, 1, 1);

    func_08035BD4(destination, 8, value, 0xD000);
    func_0808A604(2, 2);
}
