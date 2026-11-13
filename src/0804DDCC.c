// Complete target [0x0804DDCC, 0x0804DE8C), 192 bytes.
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u8 unknown_00[0x0C];
    u8 width;
    u8 height;
    u8 unknown_0E[2];
    u8 *tiles;
    u16 *map;
} Layer0804DDCC;

typedef struct {
    u16 field_00;
    u8 field_02;
    u8 field_03;
    u16 field_04;
    u8 field_06;
    u8 field_07;
    u16 field_08;
} Blend0804DDCC;

extern Layer0804DDCC data_03000990;
extern Blend0804DDCC *func_0804CAB0(void);
extern void *func_0804CA8C(void);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08000B20(void *request, u32 value, void *destination, u32 count);

void func_0804DDCC(u8 fade_in, u16 speed)
{
    Blend0804DDCC *blend = func_0804CAB0();
    u16 fill;
    u16 *source;

    source = &fill;
    *source = 0x1111;
    func_0814186C(source, data_03000990.tiles + 0x7FE0, 0x01000010);
    func_08000B20(func_0804CA8C(), 0xC3FF, data_03000990.map,
                  data_03000990.width * data_03000990.height);
    blend->field_08 = 0;
    blend->field_00 = 0;
    if (fade_in) {
        blend->field_02 = 0x10;
        blend->field_03 = 0;
    } else {
        blend->field_02 = 0;
        blend->field_03 = 0x10;
    }
    blend->field_04 = speed;
    if (fade_in) {
        blend->field_06 = 0;
        blend->field_07 = 0x10;
    } else {
        blend->field_06 = 0x10;
        blend->field_07 = 0;
    }
    g_control_flags_03000940.bldcnt_lo = 0x48;
    g_control_flags_03000940.bldcnt_hi = 0x33;
    g_control_flags_03000940.bldalpha_lo = blend->field_02;
    g_control_flags_03000940.bldalpha_hi = blend->field_03;
}
