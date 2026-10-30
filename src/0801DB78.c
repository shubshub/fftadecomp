#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 field_10;
    u8 unknown_11;
    u16 field_12;
} State0801DB78;

extern State0801DB78 data_02007F10;
extern void func_08000D90(u32 channel);

/* Complete target: [0x0801DB78, 0x0801DB98), 32 bytes.
 * 10b5064c608aff2804d00220e3f704f90020207410bc01bc00470000107f0002
 */
void func_0801DB78(void)
{
    if (data_02007F10.field_12 != 0xFF) {
        func_08000D90(2);
        data_02007F10.field_10 = 0;
    }
}
