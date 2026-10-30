#include "ffta.h"

extern u8 data_020101F8[];
extern void func_080C034C(void *object, u32 value);

/* 080C144C..080C1460: 00 B5 01 1C 02 48 FE F7 7B FF 01 BC 00 47 00 00 F8 01 01 02. */
void func_080C144C(u32 value)
{
    func_080C034C(data_020101F8, value);
}
