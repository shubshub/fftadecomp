#include "ffta.h"

/* Complete target: [0x08137EC4, 0x08138014), 336 bytes including literals. */

typedef struct {
    u8 unknown_00[0x0C];
    u8 width;
    u8 height;
    u8 unknown_0E[0x06];
    u16 *map;
} Layer08137EC4;

extern u8 data_02003CB0[];
extern u8 data_06008000[];
extern u8 data_06008A40[];
extern u8 data_06009280[];
extern u8 data_0600AEE0[];
extern u8 data_06012400[];
extern u8 data_06012500[];
extern u8 data_06013600[];
extern Layer08137EC4 data_03000E60;
extern Layer08137EC4 data_03000E80;
extern Layer08137EC4 data_030008B0;
extern Layer08137EC4 data_03000990;
extern const u8 data_083A94CC[];
extern const u8 data_083A9CA4[];
extern const u8 data_083A93AC[];
extern const u8 data_083B4214[];
extern const u8 data_083BBA38[];
extern const u8 data_083BBC7C[];
extern const u8 data_083B53A4[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern s32 func_08005318(const void *data, u8 *output, u16 start, u16 count);
extern void func_0800543C(void *destination, const void *source);
extern void func_08137C4C(void);

void func_08137EC4(void)
{
    u16 fill_e60;
    u16 *source_e60;
    u16 fill_e80;
    u16 *source_e80;
    u16 fill_8b0;
    u16 *source_8b0;
    u16 fill_990;
    u16 *source_990;
    u8 *buffer = data_02003CB0;

    /* Four CpuFill16s of width * height halfwords (0x08137ECA-0x08137F22):
     * the SDK's vu16 temporary, spelled through a pointer until
     * fftadecomp-kit#164, as src/08087300.c clears the same four layers. */
    source_e60 = &fill_e60;
    *source_e60 = 0;
    func_0814186C(source_e60, data_03000E60.map,
                  (data_03000E60.width * data_03000E60.height) | 0x01000000);
    source_e80 = &fill_e80;
    *source_e80 = 0;
    func_0814186C(source_e80, data_03000E80.map,
                  (data_03000E80.width * data_03000E80.height) | 0x01000000);
    source_8b0 = &fill_8b0;
    *source_8b0 = 0;
    func_0814186C(source_8b0, data_030008B0.map,
                  (data_030008B0.width * data_030008B0.height) | 0x01000000);
    source_990 = &fill_990;
    *source_990 = 0;
    func_0814186C(source_990, data_03000990.map,
                  (data_03000990.width * data_03000990.height) | 0x01000000);

    func_08005318(data_083A94CC, buffer, 0, 0);
    func_0814186C(buffer, data_06008000, 0x520);
    func_08005318(data_083A9CA4, buffer, 0, 0);
    func_0814186C(buffer, data_06008A40, 0x420);
    func_0800543C(buffer, data_083B4214);
    func_0814186C(buffer, data_06009280, 0xE30);
    func_0800543C(buffer, data_083BBA38);
    func_0814186C(buffer, data_0600AEE0, 0x340);
    func_08005318(data_083A93AC, buffer, 0, 0);
    func_0814186C(buffer, data_06012400, 0x80);
    func_0800543C(buffer, data_083BBC7C);
    func_0814186C(buffer, data_06012500, 0x880);
    func_0800543C(buffer, data_083B53A4);
    func_0814186C(buffer, data_06013600, 0x440);
    func_08137C4C();
}
