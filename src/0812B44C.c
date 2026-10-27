#include "ffta.h"

typedef struct TransferRecord TransferRecord;
extern void func_08000ADC(TransferRecord *entry, const void *source,
                         void *destination, u16 words);

/* Complete [0x0812B44C, 0x0812B468): 28 bytes, 13 instructions. */
void func_0812B44C(TransferRecord *entry, const u8 *source,
                   void *destination, u8 index)
{
    func_08000ADC(entry, source + index * 0x2100, destination, 0x840);
}
