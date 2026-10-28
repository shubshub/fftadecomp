#include "ffta.h"

typedef struct TransferRecord TransferRecord;

extern u8 data_02003CB0[];
extern const u8 data_083C5454[];
extern void func_08005318(const void *table, void *destination,
                         u32 index, u32 flag);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                         void *destination, u16 words);

/* Complete [0x0812B41C, 0x0812B44C): 48 bytes, 18 instructions. */
void func_0812B41C(TransferRecord *entry, void *destination, u8 index)
{
    u8 *buffer = data_02003CB0;

    func_08005318(data_083C5454, buffer, index, 1);
    func_08000ADC(entry, buffer, destination, 0xC0);
}
