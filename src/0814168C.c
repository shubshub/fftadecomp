#include "ffta.h"

/* Target: complete [0x0814168C, 0x081416D2), 70 bytes, 28 instructions.
 * Record views retain only the observed halfword at +4. */
typedef struct {
    u8 unknown_00[4];
    u16 value;
} Record0814168C;

extern u8 data_020084D8;
extern Record0814168C data_0200F2E0;
extern Record0814168C data_0200F320;

u32 func_0814168C(u16 selector)
{
    Record0814168C *record = 0;

    if (data_020084D8 & 2) {
        switch (selector) {
        case 1:
            record = &data_0200F2E0;
            break;
        case 2:
            record = &data_0200F320;
            break;
        }
        if (record != 0) {
            u32 result = record->value;

            if (result != 0)
                result = 1;
            return result;
        }
    }
    return 0;
}
