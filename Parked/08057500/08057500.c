#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 unknown_12[0x6A];
    void *item;
    void *context;
    u8 unknown_84[0x1000];
    u8 field_1084;
    u8 field_1085;
    u8 field_1086;
    u8 field_1087;
    u8 field_1088;
    u8 unknown_1089;
    u8 field_108A;
    u8 field_108B;
} State;

typedef struct {
    u8 unknown_0000[0x1C58];
    State display;
    u8 unknown_2CE4[0x56];
    u8 unit_ids[0];
} MenuState08057500;

typedef struct {
    u8 unknown_00[9];
    u8 value_09;
    u8 unknown_0A[0xFE];
} Unit08057500;

extern MenuState08057500 *data_0200F428;
extern Unit08057500 g_state_02000080[];
extern u16 func_08022238(void *object, u8 *output);
extern void func_08029C34(State *state, u8 value, u8 first, u8 second,
                         u8 fourth, u8 fifth, u8 sixth);

/* Complete [0x08057500, 0x08057578): 120 bytes, 49 instructions.
 * Target: 70b5464640b484b0041c2406240e164e30681649884640440019017848014018c000134d401903a9caf786fe021c1206120e31680f4bc818414409190b785901c918c9006d18697a03ab1b7800930123019300230293d2f76dfb04b008bc984670bc01bc0047000028f400023a2d000080000002581c0000.
 */
void func_08057500(u8 index)
{
    u8 output;
    u8 value;

    value = (u8)func_08022238(
        &g_state_02000080[data_0200F428->unit_ids[index]], &output);
    func_08029C34(&data_0200F428->display,
                  g_state_02000080[data_0200F428->unit_ids[index]].value_09,
                  value, 0, output, 1, 0);
}
