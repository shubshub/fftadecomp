#include "ffta.h"

typedef struct State08017424 State08017424;

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 field_03;
    u32 unknown_04;
    u16 field_08;
    u8 field_0a;
    u8 unknown_0b;
} Record0803FAA4;

typedef struct {
    u8 unknown_00[0x0c];
    Record0803FAA4 record;
} Source0803FAA4;

/* The observed record stride is 0xCC; its count is unknown. */
typedef struct {
    u32 field_00;
    u8 unknown_04[0x14];
    u32 field_18;
    u16 field_1c;
    u8 unknown_1e[0xae];
} Slot0803FAA4;

typedef struct {
    u8 unknown_00[0x968];
    Slot0803FAA4 slots[0];
} State0803FAA4;

/* The observed resource stride is 0x4C. */
typedef struct {
    u8 unknown_00[0x28];
    u8 field_28;
    u8 unknown_29[0x23];
} Resource0803FAA4;

extern State0803FAA4 *g_state_03002810;
extern Resource0803FAA4 data_030009E0[];
extern void func_08017424(State08017424 *, u32, u32,
                          u8, u8, u8, u8, u16, u8, u16, u16, u8);
extern void func_08016C90(State08017424 *, u8);

/* 0x0803FAA4..0x0803FB50: complete 172-byte target.
 * f0b5474680b48bb0884611991b061b0e09060d0e08a90c32d0cad0c11f4e3168
 * cc22041c544309191d4809180f88ff2b02d008a8037045700125326819495018
 * 001901689826360192191219126808a803784078009008a88078019008a8c078
 * 029008a8008903900f4c4c20784300192830007804900520059006950c200790
 * 4046d7f77dfc08a8817a4046d7f7aef80bb008bc9846f0bc01bc004710280003
 * 8409000068090000e0090003
 */
void func_0803FAA4(u32 index, State08017424 *state,
                   const Source0803FAA4 *source, u8 first, u8 second)
{
    Record0803FAA4 record = source->record;
    u16 resource = g_state_03002810->slots[index].field_1c;

    if (first != 0xff) {
        record.field_00 = first;
        record.field_01 = second;
    }
    func_08017424(state,
        g_state_03002810->slots[index].field_00,
        g_state_03002810->slots[index].field_18,
        record.field_00, record.field_01, record.field_02, record.field_03,
        record.field_08, data_030009E0[resource].field_28, 5, 1, 12);
    func_08016C90(state, record.field_0a);
}
