#include "ffta.h"

/* Target: complete [0x08141D9C, 0x08141E30), 148 bytes. */
typedef struct {
    const void *operations[5];
    u8 parameters[0x14];
    u8 maker;
    u8 device;
} DeviceRecord;

extern u16 data_04000204;
extern const void *data_0836CE38[];
extern const void *data_0200F36C;
extern const void *data_0200F378;
extern const void *data_0200F37C;
extern const void *data_0200F368;
extern const void *data_0200F380;
extern const u8 *data_0200F370;
extern u16 func_081418C0(void);

u32 func_08141D9C(void)
{
    u16 identifier;
    const void **entry;
    u32 result;
    u16 control = data_04000204;

    control &= 0xfffc;
    control |= 3;
    data_04000204 = control;
    identifier = func_081418C0();
    entry = data_0836CE38;
    result = 1;

    while (((const DeviceRecord *)*entry)->maker != 0) {
        if (identifier == *(const u16 *)&((const DeviceRecord *)*entry)->maker) {
            result = 0;
            break;
        }
        entry++;
    }

    data_0200F36C = ((const DeviceRecord *)*entry)->operations[0];
    data_0200F378 = ((const DeviceRecord *)*entry)->operations[1];
    data_0200F37C = ((const DeviceRecord *)*entry)->operations[2];
    data_0200F368 = ((const DeviceRecord *)*entry)->operations[3];
    data_0200F380 = ((const DeviceRecord *)*entry)->operations[4];
    data_0200F370 = ((const DeviceRecord *)*entry)->parameters;
    return result;
}
