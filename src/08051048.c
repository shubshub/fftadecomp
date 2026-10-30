#include "ffta.h"

/* Complete target: [0x08051048, 0x08051084), 60 bytes.
 * 30b500210a4d0b4c0b4b00222868001940180078012802d14800c0180280481c0006
 * 010e1329f1d930bc01bc0047000028f40002481d00003c1f0002
 */
typedef struct {
    u8 unknown_0000[0x1D48];
    u8 entries[20];
} State08051048;

extern State08051048 *data_0200F428;
extern u16 data_02001F3C[20];

void func_08051048(void)
{
    u8 index;

    for (index = 0; index < 20; index++) {
        if (data_0200F428->entries[index] == 1)
            data_02001F3C[index] = 0;
    }
}
