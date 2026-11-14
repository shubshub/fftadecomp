#include "ffta.h"

// Complete target [0x08004AC0, 0x08004B9C): 220 bytes, 79 instructions.
// Pool: 0x04000208 0x03000E50 0x0000FF7F 0x04000134 0x04000128 0x00006033
//       0x030028A0 0x05000056 0x08005088 0x03002B70 0x04000010 0x080050C8
//       0x03002A00 0x04000050

typedef struct {
    u8 bytes[0x18];
} SerialBlock;

typedef struct {
    SerialBlock first;
    SerialBlock second;
    SerialBlock third;
} SerialEntry;

typedef struct {
    u8 unknown_00[9];
    u8 field_09;
    u8 selected;
    u8 unknown_0B[9];
    s32 field_14;
    u8 unknown_18[0x10];
    SerialBlock *scratch_first;
    SerialBlock *scratch_second;
    SerialBlock *first[4];
    SerialBlock *second[4];
    SerialBlock *third[4];
    SerialBlock scratch_60;
    SerialBlock scratch_78;
    SerialEntry entries[2];
    u8 unknown_120[4];
    u8 ready;
} SerialState;

extern u16 data_03000E50;
extern SerialState data_030028A0;
extern u32 data_03002B70[];
extern u32 data_03002A00[];
extern const u32 data_080050C8[];
extern const u32 data_08005088[];
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08004AC0(void)
{
    u32 fill;
    s32 i;

    *(u16 *)0x04000208 = 0;
    data_03000E50 &= 0xFF7F;
    *(u16 *)0x04000134 = 0;
    *(u16 *)0x04000128 = 0x6033;
    fill = 0;
    func_0814186C(&fill, &data_030028A0, 0x05000056);
    func_0814186C(data_08005088, data_03002B70, 0x04000010);
    func_0814186C(data_080050C8, data_03002A00, 0x04000050);
    data_030028A0.selected = 0xFF;
    data_030028A0.field_14 = -1;
    data_030028A0.scratch_first = &data_030028A0.scratch_60;
    data_030028A0.scratch_second = &data_030028A0.scratch_78;
    for (i = 0; i <= 1; i++)
    {
        data_030028A0.first[i] = &data_030028A0.entries[i].first;
        data_030028A0.second[i] = &data_030028A0.entries[i].second;
        data_030028A0.third[i] = &data_030028A0.entries[i].third;
    }
    data_030028A0.field_09 = 0;
    data_030028A0.ready = 1;
}
