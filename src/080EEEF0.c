#include "ffta.h"

/* 0x080EEEF0..0x080EEF30: complete 64-byte wrapper. */
extern const u8 data_088EA550[];
extern const u8 data_08399978[];
extern void func_080D45D0(const void *, u32, u32, u32, u32);
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);

void *func_080EEEF0(u8 variant, void *object, void *parent)
{
    func_080D45D0(data_088EA550, 6, 1, variant, 1);
    return func_080E03F8(object, data_08399978, 1, 2, 0, parent);
}
