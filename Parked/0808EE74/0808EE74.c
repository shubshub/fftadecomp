#include "ffta.h"

extern u8 data_02003CB0[];
extern u8 data_06000020[];
extern const u8 data_08393FC0[];

extern void func_080CB9E0(void *object, u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target [0808EE74, 0808EEB4), 64 bytes:
 * f0b50c4e0c4d2a2700240c4820180178301c3cf0abfd301c291c8022b2f0ecfc802040002d180134bc42eedbf0bc01bc00470000b03c000220000006c03f3908
 */
void func_0808EE74(void)
{
    s32 index;
    u8 *destination = data_06000020;

    for (index = 0; index < 42; index++) {
        func_080CB9E0(data_02003CB0, data_08393FC0[index]);
        func_0814186C(data_02003CB0, destination, 128);
        destination += 0x100;
    }
}
