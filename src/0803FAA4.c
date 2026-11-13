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
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 field_03;
    u32 unknown_04;
    u16 field_08;
    u8 field_0A;
    u8 unknown_0B;
} Descriptor0803FAA4;

typedef struct {
    u8 unknown_00[0xC];
    Descriptor0803FAA4 descriptor;
} Configuration0803FAA4;

/* The observed record stride is 0xCC; its count is unknown. */
typedef struct {
    u8 unknown_00[0x14];
    u32 field_14;
    u8 unknown_18[0x14];
    u32 field_2C;
    u16 field_30;
    u8 unknown_32[0x9A];
} Record0803FAA4;

typedef struct {
    u8 unknown_00[0x954];
    Record0803FAA4 records[0];
} Root0803FAA4;

/* The observed resource stride is 0x4C. */
typedef struct {
    u8 unknown_00[0x28];
    u8 field_28;
    u8 unknown_29[0x23];
} Resource0803FAA4;

extern Root0803FAA4 *g_state_03002810;
extern Resource0803FAA4 data_030009E0[];
extern void func_08017424(State08017424 *, u32, u32,
                          u8, u8, u8, u8, u16, u8, u16, u16, u8);
extern void func_08016C90(State08017424 *, u8);

/* 0x0803FAA4..0x0803FB50: complete 172-byte target, 76 instructions.
 * f0b5474680b48bb0884611991b061b0e09060d0e08a90c32d0cad0c11f4e3168
 * cc22041c544309191d4809180f88ff2b02d008a8037045700125326819495018
 * 001901689826360192191219126808a803784078009008a88078019008a8c078
 * 029008a8008903900f4c4c20784300192830007804900520059006950c200790
 * 4046d7f77dfc08a8817a4046d7f7aef80bb008bc9846f0bc01bc004710280003
 * 8409000068090000e0090003
 */
void func_0803FAA4(u32 index, State08017424 *state,
                   const Configuration0803FAA4 *configuration,
                   u8 first, u8 second)
{
    Descriptor0803FAA4 descriptor = configuration->descriptor;
    u16 identifier = g_state_03002810->records[index].field_30;
    u16 enabled;

    if (first != 0xFF) {
        descriptor.field_00 = first;
        descriptor.field_01 = second;
    }
    enabled = 1;
    func_08017424(state, g_state_03002810->records[index].field_14,
                   g_state_03002810->records[index].field_2C,
                   descriptor.field_00, descriptor.field_01,
                   descriptor.field_02, descriptor.field_03,
                   descriptor.field_08, data_030009E0[identifier].field_28,
                   5, enabled, 12);
    func_08016C90(state, descriptor.field_0A);
}
