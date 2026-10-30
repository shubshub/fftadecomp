#include "ffta.h"

/* Target 0x08025464..0x080254A0, 60 bytes:
 * 10b5054c2068002802d0006a002805d1012040420fe0000038f40002e0f7d0fa21688878002801d1002004e00020887020680021405e10bc02bc0847
 */
typedef struct {
    s16 halfword_00;
    u8 byte_02;
    u8 unknown_03[0x1D];
    void *manager;
} Context08025464;

extern Context08025464 *data_0200F438;
extern void func_08005A24(void *manager);

s32 func_08025464(void)
{
    s32 result;

    if (data_0200F438 == 0 || data_0200F438->manager == 0)
        return -1;
    func_08005A24(data_0200F438->manager);
    if (data_0200F438->byte_02 == 0) {
        result = 0;
    } else {
        data_0200F438->byte_02 = 0;
        result = data_0200F438->halfword_00;
    }
    return result;
}
