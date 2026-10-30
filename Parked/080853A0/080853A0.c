#include "ffta.h"

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017424;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u32 unknown_04;
    u16 flags;
    u8 mode;
    u8 unknown_0B;
} Descriptor080853A0;

typedef struct {
    u8 unknown_00[0xC];
    Descriptor080853A0 descriptor;
} Configuration080853A0;

typedef struct {
    u8 unknown_00[0x14];
    u32 field_14;
    u8 unknown_18[0x14];
    u32 field_2C;
    u16 field_30;
    u8 unknown_32[0x9A];
} Record080853A0;

typedef struct {
    u8 unknown_00[0x2C88];
    Record080853A0 records[0];
} Root080853A0;

typedef struct {
    u8 unknown_00[0x28];
    u8 field_28;
    u8 unknown_29[0x23];
} Resource080853A0;

extern Root080853A0 *data_03002818;
extern Resource080853A0 data_030009E0[];
extern void func_08017424(State08017424 *state, u32 value_00, u32 value_04,
                         u8 value_10, u8 value_11, u8 value_12, u8 value_13,
                         u16 value_14, u8 value_16, u16 value_18,
                         u16 value_1A, u8 value_17);
extern void func_08016C90(State08017424 *state, u8 mode);

/* Complete target: [0x080853A0, 0x08085450), 176 bytes.
 * f0b5474680b48bb0884611991b061b0e09060d0e08a90c32d0cad0c11f4e3168
 * cc22041c544309191d4809180f88ff2b02d008a8037045700125326819495018
 * 00190168184e92191219126808a803784078009008a88078019008a8c0780290
 * 08a800890390114c4c20784300192830007804900520059006950c2007904046
 * 92f700f808a8817a404691f731fc0bb008bc9846f0bc01bc0047000018280003
 * b82c00009c2c0000b42c0000e0090003
 */
void func_080853A0(u32 index, State08017424 *state,
                   const Configuration080853A0 *configuration, u8 x, u8 y)
{
    Descriptor080853A0 descriptor = configuration->descriptor;
    u16 selection = data_03002818->records[index].field_30;

    if (x != 0xFF) {
        descriptor.x = x;
        descriptor.y = y;
    }
    {
        u32 value_00 = data_03002818->records[index].field_14;
        u32 value_04 = data_03002818->records[index].field_2C;

        func_08017424(state, value_00, value_04,
                 descriptor.x, descriptor.y, descriptor.width, descriptor.height,
                 descriptor.flags, data_030009E0[selection].field_28, 5, 1, 12);
    }
    func_08016C90(state, descriptor.mode);
}
