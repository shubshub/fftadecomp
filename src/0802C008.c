#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Entry0802BA08;

typedef struct TransferRecord TransferRecord;

extern Entry0802BA08 *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

/* Complete [0x0802C008, 0x0802C034): 44 bytes.
 * 30b5041c0d1c2404240c2d042d0cfff7f7fc054964186d18211c2a1c0823d4f759fd30bc01bc004700390106
 */
void func_0802C008(u16 source_offset, u16 destination_offset)
{
    Entry0802BA08 *entry = func_0802BA08();
    u8 *base = (u8 *)0x06013900;

    /* The opaque allocated entry is used through its transfer-record view. */
    func_08000ADC((TransferRecord *)entry, base + source_offset,
                  base + destination_offset, 8);
}
